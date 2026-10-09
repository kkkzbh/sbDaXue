"""
刺杀博弈 - 不完全信息博弈建模
核心博弈逻辑：完美贝叶斯均衡、逆向归纳
"""

import random
import secrets
from typing import Dict, Optional, Tuple, Union
from fractions import Fraction

EPS = 1e-9  # 用于策略计算的精度
BELIEF_EPS = 1e-4  # 用于信念验证的精度（允许用户输入有一定误差）


class AssassinationGame:
    """刺杀博弈游戏类
    
    参与者:
    - 迈克 (Mike): 计算机扮演，先行动
    - 杀手 (Killer): 人类玩家扮演，后行动
    
    状态:
    - gun: 持枪
    - empty: 空手
    
    迈克行动:
    - guard: 把守
    - hide: 躲避
    
    杀手行动:
    - kill: 刺杀
    - leave: 离开
    """
    
    def __init__(self, seed: Optional[int] = None, prior_gun: Optional[float] = None):
        """初始化游戏
        
        Args:
            seed: 随机种子，用于可复现性。若为 None 则使用安全随机数
            prior_gun: 固定先验概率 P(持枪)（可选）。若为 None 则随机生成
        """
        if seed is None:
            seed = secrets.randbelow(2**32)
        self.seed = seed
        self.rng = random.Random(seed)
        
        if prior_gun is not None and not (0 <= prior_gun <= 1):
            raise ValueError(f"prior_gun = {prior_gun} 须在 [0,1] 范围内")

        # 自然决定的持枪概率（对玩家不公开）
        self.p_gun = float(prior_gun) if prior_gun is not None else self.rng.random()
        self.p_empty = 1 - self.p_gun
        
        # 实际状态（根据概率随机决定）
        self.actual_state: Optional[str] = None
        
        # 收益矩阵: payoff[state][mike_action][killer_action] = (mike_payoff, killer_payoff)
        # 默认收益矩阵
        self.payoff: Dict[str, Dict[str, Dict[str, Tuple[float, float]]]] = {
            'gun': {
                'guard': {'kill': (2, -2), 'leave': (3, 0)},
                'hide': {'kill': (0, 1), 'leave': (1, 0)}
            },
            'empty': {
                'guard': {'kill': (-1, 2), 'leave': (1, 0)},
                'hide': {'kill': (-2, 3), 'leave': (0, 0)}
            }
        }
        
        # 杀手对迈克状态的信念
        # killer_beliefs[mike_action] = {'gun': prob, 'empty': prob}
        self.killer_beliefs: Optional[Dict[str, Dict[str, float]]] = None
        
        # 迈克的策略（由逆向归纳计算）
        # mike_strategy[state][action] = probability
        self.mike_strategy: Optional[Dict[str, Dict[str, float]]] = None
        
        # 杀手的最优反应
        # killer_response[mike_action] = {'type': 'pure'/'mixed', 'action': str/'p_kill': float}
        self.killer_response: Optional[Dict[str, dict]] = None
        
        # 游戏状态
        self.mike_action: Optional[str] = None
        self.killer_action: Optional[str] = None
        self.game_result: Optional[dict] = None
    
    def parse_belief(self, value: Union[str, float]) -> float:
        """解析信念值，支持分数和小数
        
        Args:
            value: 信念值，可以是 "2/3", "0.667" 或浮点数
            
        Returns:
            解析后的浮点数概率值
        """
        if isinstance(value, (int, float)):
            return float(value)
        
        value_str = str(value).strip()
        if '/' in value_str:
            parts = value_str.split('/')
            if len(parts) != 2:
                raise ValueError(f"分数格式错误: {value_str!r}，应为 'a/b'")

            try:
                return float(Fraction(value_str))
            except (ValueError, ZeroDivisionError):
                try:
                    num = float(parts[0])
                    denom = float(parts[1])
                except ValueError as e:
                    raise ValueError(f"无法解析分数: {value_str!r}") from e
                if denom == 0:
                    raise ValueError("分母不能为0")
                return num / denom

        try:
            return float(value_str)
        except ValueError as e:
            raise ValueError(f"无法解析数值: {value_str!r}") from e
    
    def set_payoff_matrix(self, payoff: Dict[str, Dict[str, Dict[str, Tuple[float, float]]]]):
        """设置收益矩阵
        
        Args:
            payoff: 收益矩阵字典
        """
        self.payoff = payoff
    
    def set_killer_beliefs(self, guard_gun: Union[str, float], hide_gun: Union[str, float]):
        """设置杀手对迈克状态的信念
        
        Args:
            guard_gun: P(持枪|把守)，支持分数如 "2/3"
            hide_gun: P(持枪|躲避)，支持分数如 "0"
        """
        p_guard_gun = self.parse_belief(guard_gun)
        p_hide_gun = self.parse_belief(hide_gun)
        
        if not (0 <= p_guard_gun <= 1):
            raise ValueError(f"P(持枪|把守) = {p_guard_gun} 须在 [0,1] 范围内")
        if not (0 <= p_hide_gun <= 1):
            raise ValueError(f"P(持枪|躲避) = {p_hide_gun} 须在 [0,1] 范围内")
        
        self.killer_beliefs = {
            'guard': {'gun': p_guard_gun, 'empty': 1 - p_guard_gun},
            'hide': {'gun': p_hide_gun, 'empty': 1 - p_hide_gun}
        }
    
    def compute_killer_best_response(self, mike_action: str) -> dict:
        """计算杀手对迈克行动的最优反应
        
        Args:
            mike_action: 迈克的行动 ('guard' 或 'hide')
            
        Returns:
            杀手的最优反应策略
        """
        if self.killer_beliefs is None:
            raise ValueError("杀手信念未设置")
        
        belief = self.killer_beliefs[mike_action]
        
        # 计算刺杀的期望收益
        E_kill = (belief['gun'] * self.payoff['gun'][mike_action]['kill'][1] +
                  belief['empty'] * self.payoff['empty'][mike_action]['kill'][1])
        
        # 计算离开的期望收益
        E_leave = (belief['gun'] * self.payoff['gun'][mike_action]['leave'][1] +
                   belief['empty'] * self.payoff['empty'][mike_action]['leave'][1])
        
        if abs(E_kill - E_leave) < EPS:
            # 无差异，混合策略
            return {'type': 'mixed', 'p_kill': 0.5, 'E_kill': E_kill, 'E_leave': E_leave}
        elif E_kill > E_leave:
            return {'type': 'pure', 'action': 'kill', 'E_kill': E_kill, 'E_leave': E_leave}
        else:
            return {'type': 'pure', 'action': 'leave', 'E_kill': E_kill, 'E_leave': E_leave}
    
    def compute_mike_payoff(self, state: str, action: str) -> float:
        """计算迈克在给定状态和行动下的期望收益
        
        Args:
            state: 迈克的状态 ('gun' 或 'empty')
            action: 迈克的行动 ('guard' 或 'hide')
            
        Returns:
            迈克的期望收益
        """
        if self.killer_response is None:
            raise ValueError("杀手反应未计算")
        
        killer_resp = self.killer_response[action]
        
        if killer_resp['type'] == 'pure':
            killer_action = killer_resp['action']
            return self.payoff[state][action][killer_action][0]
        else:
            # 混合策略
            p_kill = killer_resp['p_kill']
            return (p_kill * self.payoff[state][action]['kill'][0] +
                    (1 - p_kill) * self.payoff[state][action]['leave'][0])
    
    def compute_equilibrium(self):
        """使用逆向归纳计算均衡策略
        
        返回迈克的最优策略
        """
        if self.killer_beliefs is None:
            raise ValueError("杀手信念未设置")
        
        # Step 1: 计算杀手对每种迈克行动的最优反应
        self.killer_response = {
            'guard': self.compute_killer_best_response('guard'),
            'hide': self.compute_killer_best_response('hide')
        }
        
        # Step 2: 计算迈克在每种状态下的最优行动
        self.mike_strategy = {}
        
        for state in ['gun', 'empty']:
            E_guard = self.compute_mike_payoff(state, 'guard')
            E_hide = self.compute_mike_payoff(state, 'hide')
            
            if abs(E_guard - E_hide) < EPS:
                # 无差异，混合策略（默认各50%）
                self.mike_strategy[state] = {
                    'guard': 0.5, 'hide': 0.5,
                    'type': 'mixed', 'E_guard': E_guard, 'E_hide': E_hide
                }
            elif E_guard > E_hide:
                self.mike_strategy[state] = {
                    'guard': 1.0, 'hide': 0.0,
                    'type': 'pure', 'best_action': 'guard',
                    'E_guard': E_guard, 'E_hide': E_hide
                }
            else:
                self.mike_strategy[state] = {
                    'guard': 0.0, 'hide': 1.0,
                    'type': 'pure', 'best_action': 'hide',
                    'E_guard': E_guard, 'E_hide': E_hide
                }
    
    def determine_actual_state(self):
        """根据自然概率确定迈克的实际状态"""
        if self.rng.random() < self.p_gun:
            self.actual_state = 'gun'
        else:
            self.actual_state = 'empty'
    
    def execute_mike_action(self) -> Tuple[str, Dict[str, float]]:
        """执行迈克的行动
        
        Returns:
            (mike_action, conditional_probs): 迈克的行动和条件概率
        """
        if self.mike_strategy is None:
            self.compute_equilibrium()

        # 迈克在一局中只行动一次：重复请求返回同一结果，避免前端重复拉取导致状态不一致
        if self.mike_action is not None:
            strategy = self.mike_strategy[self.actual_state]
            conditional_probs = {
                'P(guard|state)': strategy['guard'],
                'P(hide|state)': strategy['hide']
            }
            return self.mike_action, conditional_probs
        
        if self.actual_state is None:
            self.determine_actual_state()
        
        strategy = self.mike_strategy[self.actual_state]
        
        # 根据策略概率选择行动
        if self.rng.random() < strategy['guard']:
            self.mike_action = 'guard'
        else:
            self.mike_action = 'hide'
        
        # 返回条件概率
        conditional_probs = {
            'P(guard|state)': strategy['guard'],
            'P(hide|state)': strategy['hide']
        }
        
        return self.mike_action, conditional_probs
    
    def submit_killer_action(self, action: str) -> dict:
        """提交杀手的行动并计算结果
        
        Args:
            action: 杀手的行动 ('kill' 或 'leave')
            
        Returns:
            游戏结果
        """
        if action not in ['kill', 'leave']:
            raise ValueError(f"无效的杀手行动: {action}")
        
        if self.mike_action is None:
            raise ValueError("迈克尚未行动")
        
        self.killer_action = action
        
        # 计算实际收益
        mike_payoff, killer_payoff = self.payoff[self.actual_state][self.mike_action][action]
        
        self.game_result = {
            'actual_state': self.actual_state,
            'mike_action': self.mike_action,
            'killer_action': action,
            'mike_payoff': mike_payoff,
            'killer_payoff': killer_payoff,
            'winner': 'mike' if mike_payoff > killer_payoff else ('killer' if killer_payoff > mike_payoff else 'tie')
        }
        
        return self.game_result
    
    def verify_beliefs(self) -> dict:
        """使用贝叶斯法则验证杀手信念
        
        Returns:
            验证结果
        """
        if self.mike_strategy is None or self.killer_beliefs is None:
            raise ValueError("策略或信念未设置")
        
        results = {}
        all_match = True
        
        for action in ['guard', 'hide']:
            # 计算迈克选择该行动的总概率
            # P(action) = P(gun) * P(action|gun) + P(empty) * P(action|empty)
            p_action = (self.p_gun * self.mike_strategy['gun'][action] +
                        self.p_empty * self.mike_strategy['empty'][action])
            
            if p_action < EPS:
                # 该行动概率为0，不在均衡路径上
                results[action] = {
                    'on_path': False,
                    'message': f'{action}未发生（概率为0），跳过验证'
                }
                continue
            
            # 使用贝叶斯法则计算后验概率
            # P(gun|action) = P(action|gun) * P(gun) / P(action)
            posterior_gun = (self.mike_strategy['gun'][action] * self.p_gun) / p_action
            
            # 获取玩家输入的信念
            player_belief = self.killer_beliefs[action]['gun']
            
            # 比较后验概率和玩家信念
            match = abs(posterior_gun - player_belief) < BELIEF_EPS
            
            results[action] = {
                'on_path': True,
                'match': match,
                'posterior_gun': posterior_gun,
                'player_belief_gun': player_belief,
                'p_action': p_action
            }
            
            if not match:
                all_match = False
        
        return {
            'pbe_established': all_match,
            'details': results,
            'p_gun': self.p_gun,
            'p_empty': self.p_empty
        }
    
    def get_equilibrium_summary(self) -> dict:
        """获取均衡策略的摘要
        
        Returns:
            均衡策略摘要
        """
        if self.mike_strategy is None or self.killer_response is None:
            raise ValueError("均衡未计算")
        
        return {
            'mike_strategy': self.mike_strategy,
            'killer_response': self.killer_response,
            'payoff_matrix': self.payoff,
            'killer_beliefs': self.killer_beliefs
        }
    
    def reset(self, new_seed: Optional[int] = None, reset_prior: bool = False):
        """重置游戏状态

        Args:
            new_seed: 新的随机种子
            reset_prior: 是否重置先验概率 p_gun（默认保留）
        """
        if new_seed is not None:
            self.seed = new_seed
            self.rng = random.Random(self.seed)
        else:
            self.seed = secrets.randbelow(2**32)
            self.rng = random.Random(self.seed)

        # 只有明确要求时才重置先验概率
        if reset_prior:
            self.p_gun = self.rng.random()
            self.p_empty = 1 - self.p_gun

        self.actual_state = None
        self.mike_action = None
        self.killer_action = None
        self.game_result = None
        # 保留收益矩阵、信念和先验概率，只重置游戏状态


class GameManager:
    """游戏管理器，管理多个游戏实例"""
    
    def __init__(self):
        self.games: Dict[str, AssassinationGame] = {}
        self._id_counter = 0
    
    def create_game(self, seed: Optional[int] = None, prior_gun: Optional[float] = None) -> str:
        """创建新游戏
        
        Returns:
            游戏ID
        """
        self._id_counter += 1
        game_id = f"game_{self._id_counter}"
        self.games[game_id] = AssassinationGame(seed=seed, prior_gun=prior_gun)
        return game_id
    
    def get_game(self, game_id: str) -> AssassinationGame:
        """获取游戏实例"""
        if game_id not in self.games:
            raise KeyError(f"游戏 {game_id} 不存在")
        return self.games[game_id]
    
    def delete_game(self, game_id: str):
        """删除游戏"""
        if game_id not in self.games:
            raise KeyError(f"游戏 {game_id} 不存在")
        del self.games[game_id]


# 全局游戏管理器
game_manager = GameManager()
