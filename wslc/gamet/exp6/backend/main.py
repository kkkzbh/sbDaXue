"""
FastAPI 后端入口
刺杀博弈 - 不完全信息博弈建模
"""

from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from typing import Optional

from bayesian_game_ import game_manager, AssassinationGame
from schemas import (
    GameCreateRequest, GameCreateResponse,
    PayoffMatrixRequest,
    BeliefRequest,
    KillerActionRequest,
    MikeActionResponse, GameResultResponse,
    BeliefVerificationResponse, BeliefVerificationDetail,
    EquilibriumSummaryResponse,
    ErrorResponse
)

app = FastAPI(
    title="刺杀博弈游戏 API",
    description="不完全信息博弈建模 - 完美贝叶斯均衡实验",
    version="1.0.0"
)

# CORS 配置
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# 中文翻译映射
STATE_CN = {'gun': '持枪', 'empty': '空手'}
MIKE_ACTION_CN = {'guard': '把守', 'hide': '躲避'}
KILLER_ACTION_CN = {'kill': '刺杀', 'leave': '离开'}
WINNER_CN = {'mike': '迈克获胜', 'killer': '杀手获胜', 'tie': '平局'}


@app.get("/")
async def root():
    """API 根路径"""
    return {"message": "刺杀博弈游戏 API", "version": "1.0.0"}


@app.post("/game/new", response_model=GameCreateResponse)
async def create_game(request: Optional[GameCreateRequest] = None):
    """创建新游戏
    
    返回游戏 ID，后续操作需要使用此 ID
    """
    seed = request.seed if request else None
    prior_gun = request.prior_gun if request else None
    game_id = game_manager.create_game(seed=seed, prior_gun=prior_gun)
    return GameCreateResponse(
        game_id=game_id,
        message="游戏创建成功，请设置收益矩阵和杀手信念"
    )


@app.post("/game/{game_id}/payoff")
async def set_payoff(game_id: str, request: PayoffMatrixRequest):
    """设置收益矩阵
    
    收益矩阵包含两张 2×2 表格：
    - gun（持枪）状态下的收益
    - empty（空手）状态下的收益
    
    每种状态下有迈克的两个行动（guard/hide），
    以及杀手的两个行动（kill/leave）
    """
    try:
        game = game_manager.get_game(game_id)
    except KeyError:
        raise HTTPException(status_code=404, detail=f"游戏 {game_id} 不存在")
    
    payoff = request.to_game_format()
    game.set_payoff_matrix(payoff)
    
    return {"message": "收益矩阵设置成功", "payoff": payoff}


@app.post("/game/{game_id}/beliefs")
async def set_beliefs(game_id: str, request: BeliefRequest):
    """设置杀手对迈克状态的信念
    
    输入两个条件概率：
    - guard_gun: P(持枪|把守)
    - hide_gun: P(持枪|躲避)
    
    支持分数格式（如 "2/3"）和小数格式（如 "0.667"）
    """
    try:
        game = game_manager.get_game(game_id)
    except KeyError:
        raise HTTPException(status_code=404, detail=f"游戏 {game_id} 不存在")
    
    try:
        game.set_killer_beliefs(request.guard_gun, request.hide_gun)
        game.compute_equilibrium()
    except ValueError as e:
        raise HTTPException(status_code=400, detail=str(e))
    
    # 返回杀手信念和计算出的最优反应
    return {
        "message": "杀手信念设置成功，均衡策略已计算",
        "killer_beliefs": game.killer_beliefs,
        "killer_response": game.killer_response
    }


@app.get("/game/{game_id}/mike-action", response_model=MikeActionResponse)
async def get_mike_action(game_id: str):
    """获取迈克的行动
    
    根据均衡策略和自然决定的状态，返回迈克的行动和条件概率
    """
    try:
        game = game_manager.get_game(game_id)
    except KeyError:
        raise HTTPException(status_code=404, detail=f"游戏 {game_id} 不存在")
    
    if game.killer_beliefs is None:
        raise HTTPException(status_code=400, detail="请先设置杀手信念")
    
    try:
        action, cond_probs = game.execute_mike_action()
    except ValueError as e:
        raise HTTPException(status_code=400, detail=str(e))
    
    return MikeActionResponse(
        mike_action=action,
        action_cn=MIKE_ACTION_CN[action],
        conditional_probs=cond_probs,
        killer_response_info=game.killer_response
    )


@app.post("/game/{game_id}/killer-action", response_model=GameResultResponse)
async def submit_killer_action(game_id: str, request: KillerActionRequest):
    """提交杀手的行动
    
    杀手选择 'kill'（刺杀）或 'leave'（离开），
    返回游戏结果
    """
    try:
        game = game_manager.get_game(game_id)
    except KeyError:
        raise HTTPException(status_code=404, detail=f"游戏 {game_id} 不存在")
    
    if game.mike_action is None:
        raise HTTPException(status_code=400, detail="迈克尚未行动，请先获取迈克行动")
    
    try:
        result = game.submit_killer_action(request.action)
    except ValueError as e:
        raise HTTPException(status_code=400, detail=str(e))
    
    return GameResultResponse(
        actual_state=result['actual_state'],
        state_cn=STATE_CN[result['actual_state']],
        mike_action=result['mike_action'],
        mike_action_cn=MIKE_ACTION_CN[result['mike_action']],
        killer_action=result['killer_action'],
        killer_action_cn=KILLER_ACTION_CN[result['killer_action']],
        mike_payoff=result['mike_payoff'],
        killer_payoff=result['killer_payoff'],
        winner=result['winner'],
        winner_cn=WINNER_CN[result['winner']]
    )


@app.get("/game/{game_id}/result", response_model=BeliefVerificationResponse)
async def get_result(game_id: str):
    """获取贝叶斯验证结果
    
    使用贝叶斯法则验证玩家输入的信念是否与后验概率相符
    """
    try:
        game = game_manager.get_game(game_id)
    except KeyError:
        raise HTTPException(status_code=404, detail=f"游戏 {game_id} 不存在")
    
    if game.killer_action is None:
        raise HTTPException(status_code=400, detail="游戏尚未结束，请先提交杀手行动")
    
    try:
        verification = game.verify_beliefs()
    except ValueError as e:
        raise HTTPException(status_code=400, detail=str(e))
    
    # 构建详情响应
    details = {}
    for action, detail in verification['details'].items():
        details[action] = BeliefVerificationDetail(
            on_path=detail['on_path'],
            match=detail.get('match'),
            posterior_gun=detail.get('posterior_gun'),
            player_belief_gun=detail.get('player_belief_gun'),
            p_action=detail.get('p_action'),
            message=detail.get('message')
        )
    
    # 生成摘要
    if verification['pbe_established']:
        summary = "✅ 完美贝叶斯均衡成立！您的信念与后验概率一致。"
    else:
        mismatches = [
            MIKE_ACTION_CN[action] 
            for action, d in verification['details'].items() 
            if d.get('on_path') and not d.get('match')
        ]
        summary = f"❌ 信念不一致。在以下行动上存在偏差：{', '.join(mismatches)}。杀手判断失误，即便获胜也是纯属侥幸。"
    
    return BeliefVerificationResponse(
        pbe_established=verification['pbe_established'],
        p_gun=verification['p_gun'],
        p_empty=verification['p_empty'],
        details=details,
        summary=summary
    )


@app.get("/game/{game_id}/equilibrium", response_model=EquilibriumSummaryResponse)
async def get_equilibrium(game_id: str):
    """获取均衡策略摘要"""
    try:
        game = game_manager.get_game(game_id)
    except KeyError:
        raise HTTPException(status_code=404, detail=f"游戏 {game_id} 不存在")
    
    if game.mike_strategy is None:
        raise HTTPException(status_code=400, detail="均衡策略尚未计算，请先设置信念")
    
    summary = game.get_equilibrium_summary()
    
    return EquilibriumSummaryResponse(
        mike_strategy=summary['mike_strategy'],
        killer_response=summary['killer_response'],
        killer_beliefs=summary['killer_beliefs']
    )


@app.post("/game/{game_id}/reset")
async def reset_game(game_id: str, request: Optional[GameCreateRequest] = None):
    """重置游戏状态
    
    保留收益矩阵和信念设置，重置游戏状态（默认保持先验概率 p_gun 不变）
    """
    try:
        game = game_manager.get_game(game_id)
    except KeyError:
        raise HTTPException(status_code=404, detail=f"游戏 {game_id} 不存在")
    
    seed = request.seed if request else None
    game.reset(seed)
    
    # 如果有信念设置，重新计算均衡
    if game.killer_beliefs is not None:
        game.compute_equilibrium()
    
    return {
        "message": "游戏已重置",
        "new_seed": game.seed
    }


@app.delete("/game/{game_id}")
async def delete_game(game_id: str):
    """删除游戏"""
    try:
        game_manager.delete_game(game_id)
    except KeyError:
        raise HTTPException(status_code=404, detail=f"游戏 {game_id} 不存在")
    
    return {"message": f"游戏 {game_id} 已删除"}


if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=21447)
