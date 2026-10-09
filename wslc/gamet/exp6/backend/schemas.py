"""
Pydantic 数据模型
"""

from typing import Dict, List, Optional, Tuple, Union
from pydantic import BaseModel, Field, field_validator


class PayoffEntry(BaseModel):
    """单个收益条目"""
    mike: float = Field(..., description="迈克的收益")
    killer: float = Field(..., description="杀手的收益")


class PayoffActions(BaseModel):
    """杀手行动对应的收益"""
    kill: PayoffEntry = Field(..., description="刺杀时的收益")
    leave: PayoffEntry = Field(..., description="离开时的收益")


class MikeActions(BaseModel):
    """迈克行动对应的收益"""
    guard: PayoffActions = Field(..., description="把守时的收益")
    hide: PayoffActions = Field(..., description="躲避时的收益")


class PayoffMatrixRequest(BaseModel):
    """收益矩阵请求"""
    gun: MikeActions = Field(..., description="持枪状态的收益")
    empty: MikeActions = Field(..., description="空手状态的收益")
    
    def to_game_format(self) -> Dict[str, Dict[str, Dict[str, Tuple[float, float]]]]:
        """转换为游戏内部格式"""
        return {
            'gun': {
                'guard': {
                    'kill': (self.gun.guard.kill.mike, self.gun.guard.kill.killer),
                    'leave': (self.gun.guard.leave.mike, self.gun.guard.leave.killer)
                },
                'hide': {
                    'kill': (self.gun.hide.kill.mike, self.gun.hide.kill.killer),
                    'leave': (self.gun.hide.leave.mike, self.gun.hide.leave.killer)
                }
            },
            'empty': {
                'guard': {
                    'kill': (self.empty.guard.kill.mike, self.empty.guard.kill.killer),
                    'leave': (self.empty.guard.leave.mike, self.empty.guard.leave.killer)
                },
                'hide': {
                    'kill': (self.empty.hide.kill.mike, self.empty.hide.kill.killer),
                    'leave': (self.empty.hide.leave.mike, self.empty.hide.leave.killer)
                }
            }
        }


class BeliefRequest(BaseModel):
    """杀手信念请求"""
    guard_gun: str = Field(..., description="P(持枪|把守)，支持分数如 '2/3' 或小数 '0.667'")
    hide_gun: str = Field(..., description="P(持枪|躲避)，支持分数如 '0' 或小数 '0.5'")
    
    @field_validator('guard_gun', 'hide_gun')
    @classmethod
    def validate_belief(cls, v):
        """验证信念值格式"""
        v = str(v).strip()
        if '/' in v:
            parts = v.split('/')
            if len(parts) != 2:
                raise ValueError("分数格式错误，应为 'a/b'")
            try:
                num = float(parts[0])
                denom = float(parts[1])
                if denom == 0:
                    raise ValueError("分母不能为0")
                result = num / denom
            except ValueError as e:
                raise ValueError(f"无法解析分数: {e}")
        else:
            try:
                result = float(v)
            except ValueError:
                raise ValueError(f"无法解析数值: {v}")
        
        if not (0 <= result <= 1):
            raise ValueError(f"概率值 {result} 须在 [0,1] 范围内")
        return v


class KillerActionRequest(BaseModel):
    """杀手行动请求"""
    action: str = Field(..., description="杀手的行动: 'kill' 或 'leave'")
    
    @field_validator('action')
    @classmethod
    def validate_action(cls, v):
        if v not in ['kill', 'leave']:
            raise ValueError("行动必须是 'kill' 或 'leave'")
        return v


class GameCreateRequest(BaseModel):
    """创建游戏请求"""
    seed: Optional[int] = Field(None, description="随机种子（可选）")
    prior_gun: Optional[float] = Field(
        None,
        description="固定先验概率 P(持枪)（可选，用于预设/可复现演示；默认随机生成）"
    )

    @field_validator('prior_gun')
    @classmethod
    def validate_prior_gun(cls, v):
        if v is None:
            return v
        if not (0 <= float(v) <= 1):
            raise ValueError("prior_gun 须在 [0,1] 范围内")
        return float(v)


class GameCreateResponse(BaseModel):
    """创建游戏响应"""
    game_id: str
    message: str


class MikeActionResponse(BaseModel):
    """迈克行动响应"""
    mike_action: str = Field(..., description="迈克的行动: 'guard' 或 'hide'")
    action_cn: str = Field(..., description="行动的中文名称")
    conditional_probs: Dict[str, float] = Field(..., description="条件概率")
    killer_response_info: Dict[str, dict] = Field(..., description="杀手最优反应信息")


class GameResultResponse(BaseModel):
    """游戏结果响应"""
    actual_state: str = Field(..., description="迈克的实际状态")
    state_cn: str = Field(..., description="状态的中文名称")
    mike_action: str = Field(..., description="迈克的行动")
    mike_action_cn: str = Field(..., description="迈克行动的中文名称")
    killer_action: str = Field(..., description="杀手的行动")
    killer_action_cn: str = Field(..., description="杀手行动的中文名称")
    mike_payoff: float = Field(..., description="迈克的收益")
    killer_payoff: float = Field(..., description="杀手的收益")
    winner: str = Field(..., description="获胜者")
    winner_cn: str = Field(..., description="获胜者中文名称")


class BeliefVerificationDetail(BaseModel):
    """信念验证详情"""
    on_path: bool = Field(..., description="是否在均衡路径上")
    match: Optional[bool] = Field(None, description="信念是否与后验概率匹配")
    posterior_gun: Optional[float] = Field(None, description="贝叶斯后验概率 P(持枪|行动)")
    player_belief_gun: Optional[float] = Field(None, description="玩家输入的信念")
    p_action: Optional[float] = Field(None, description="该行动发生的概率")
    message: Optional[str] = Field(None, description="额外信息")


class BeliefVerificationResponse(BaseModel):
    """信念验证响应"""
    pbe_established: bool = Field(..., description="是否建立了完美贝叶斯均衡")
    p_gun: float = Field(..., description="自然设定的持枪概率")
    p_empty: float = Field(..., description="自然设定的空手概率")
    details: Dict[str, BeliefVerificationDetail] = Field(..., description="各行动的验证详情")
    summary: str = Field(..., description="验证结果摘要")


class EquilibriumSummaryResponse(BaseModel):
    """均衡策略摘要响应"""
    mike_strategy: Dict[str, dict] = Field(..., description="迈克的策略")
    killer_response: Dict[str, dict] = Field(..., description="杀手的最优反应")
    killer_beliefs: Dict[str, Dict[str, float]] = Field(..., description="杀手的信念")


class ErrorResponse(BaseModel):
    """错误响应"""
    detail: str = Field(..., description="错误详情")
