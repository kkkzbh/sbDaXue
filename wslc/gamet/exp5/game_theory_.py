"""
博弈论核心算法模块
实现纳什均衡求解和逆向归纳算法

讲解重点函数:
1) find_pure_nash_equilibria(): 穷举 2x2 的四个格子，找互为最优反应的纯策略均衡。
2) find_mixed_nash_equilibrium(): 用“无差异条件”解出 p、q。
3) find_all_nash_equilibria(): 汇总纯策略 + 混合策略结果。
4) backward_induction_expected_payoff(): 对不同自然状态的均衡收益做期望。
"""

import numpy as np
from typing import List, Tuple, Optional
from dataclasses import dataclass


@dataclass
class NashEquilibrium:
    """纳什均衡数据类"""
    is_pure: bool  # 是否为纯策略均衡
    player1_strategy: Tuple[float, float]  # 玩家1的策略 (策略1的概率, 策略2的概率)
    player2_strategy: Tuple[float, float]  # 玩家2的策略
    payoff1: float  # 玩家1的期望收益
    payoff2: float  # 玩家2的期望收益
    description: str  # 均衡描述
    
    def __str__(self):
        if self.is_pure:
            s1 = "策略1" if self.player1_strategy[0] == 1 else "策略2"
            s2 = "策略1" if self.player2_strategy[0] == 1 else "策略2"
            return f"纯策略纳什均衡: ({s1}, {s2}), 收益: ({self.payoff1:.2f}, {self.payoff2:.2f})"
        else:
            return (f"混合策略纳什均衡: "
                   f"玩家1 [{self.player1_strategy[0]:.3f}, {self.player1_strategy[1]:.3f}], "
                   f"玩家2 [{self.player2_strategy[0]:.3f}, {self.player2_strategy[1]:.3f}], "
                   f"期望收益: ({self.payoff1:.2f}, {self.payoff2:.2f})")


class StaticGame:
    """
    2×2静态博弈
    
    收益矩阵格式:
    player1_payoffs[i][j] 表示当玩家1选择策略i，玩家2选择策略j时，玩家1的收益
    player2_payoffs[i][j] 表示当玩家1选择策略i，玩家2选择策略j时，玩家2的收益
    
    其中 i, j ∈ {0, 1} 分别对应策略1和策略2
    """
    
    def __init__(self, 
                 player1_payoffs: np.ndarray, 
                 player2_payoffs: np.ndarray,
                 strategy1_names: Tuple[str, str] = ("策略1", "策略2"),
                 strategy2_names: Tuple[str, str] = ("策略1", "策略2")):
        """
        初始化静态博弈
        
        Args:
            player1_payoffs: 玩家1的收益矩阵 (2x2)
            player2_payoffs: 玩家2的收益矩阵 (2x2)
            strategy1_names: 玩家1的策略名称
            strategy2_names: 玩家2的策略名称
        """
        self.player1_payoffs = np.array(player1_payoffs)
        self.player2_payoffs = np.array(player2_payoffs)
        self.strategy1_names = strategy1_names
        self.strategy2_names = strategy2_names
        
        # 验证矩阵维度
        assert self.player1_payoffs.shape == (2, 2), "收益矩阵必须是2x2"
        assert self.player2_payoffs.shape == (2, 2), "收益矩阵必须是2x2"
    
    def display_payoff_matrix(self):
        """显示收益矩阵"""
        print("\n收益矩阵 (玩家1收益, 玩家2收益):")
        print(f"{'':>15} {self.strategy2_names[0]:>15} {self.strategy2_names[1]:>15}")
        for i in range(2):
            print(f"{self.strategy1_names[i]:>15}", end="")
            for j in range(2):
                payoff_str = f"({self.player1_payoffs[i,j]:.1f}, {self.player2_payoffs[i,j]:.1f})"
                print(f"{payoff_str:>15}", end="")
            print()
    
    def find_pure_nash_equilibria(self) -> List[NashEquilibrium]:
        """
        寻找所有纯策略纳什均衡
        
        Returns:
            纯策略纳什均衡列表
        """
        equilibria = []
        
        # === 1) 穷举 2x2 的四个策略组合 ===
        for i in range(2):
            for j in range(2):
                # === 2) 检查玩家1是否愿意偏离 ===
                # 若玩家1换成另一行策略得到的收益不更高，则说明“无偏离动机”
                other_i = 1 - i
                player1_no_deviation = self.player1_payoffs[i, j] >= self.player1_payoffs[other_i, j]
                
                # === 3) 检查玩家2是否愿意偏离 ===
                other_j = 1 - j
                player2_no_deviation = self.player2_payoffs[i, j] >= self.player2_payoffs[i, other_j]
                
                # === 4) 两方都不想偏离 → 该格子是纯策略纳什均衡 ===
                if player1_no_deviation and player2_no_deviation:
                    # 构造策略元组（策略1 or 策略2）
                    p1_strategy = (1.0, 0.0) if i == 0 else (0.0, 1.0)
                    p2_strategy = (1.0, 0.0) if j == 0 else (0.0, 1.0)
                    
                    equilibria.append(NashEquilibrium(
                        is_pure=True,
                        player1_strategy=p1_strategy,
                        player2_strategy=p2_strategy,
                        payoff1=self.player1_payoffs[i, j],
                        payoff2=self.player2_payoffs[i, j],
                        description=f"({self.strategy1_names[i]}, {self.strategy2_names[j]})"
                    ))
        
        return equilibria
    
    def find_mixed_nash_equilibrium(self) -> Optional[NashEquilibrium]:
        """
        寻找混合策略纳什均衡
        
        在混合策略均衡中，每个玩家通过混合策略使对手对其所有策略无差异
        
        Returns:
            混合策略纳什均衡，如果不存在则返回None
        """
        # === 1) 提取玩家1的收益矩阵元素 ===
        a11, a12 = self.player1_payoffs[0, 0], self.player1_payoffs[0, 1]
        a21, a22 = self.player1_payoffs[1, 0], self.player1_payoffs[1, 1]
        
        # === 2) 提取玩家2的收益矩阵元素 ===
        b11, b12 = self.player2_payoffs[0, 0], self.player2_payoffs[0, 1]
        b21, b22 = self.player2_payoffs[1, 0], self.player2_payoffs[1, 1]
        
        # === 3) 解玩家2的混合策略 q ===
        # 玩家1对“策略1/策略2”无差异：
        # q*a11 + (1-q)*a12 = q*a21 + (1-q)*a22
        # 整理得：q*(a11 - a12 - a21 + a22) = (a22 - a12)
        denominator1 = a11 - a12 - a21 + a22
        if abs(denominator1) < 1e-10:
            # 玩家1对玩家2的策略总是无差异，没有内点混合均衡
            return None
        
        q = (a22 - a12) / denominator1
        
        # === 4) 解玩家1的混合策略 p ===
        # 玩家2对“策略1/策略2”无差异：
        # p*b11 + (1-p)*b21 = p*b12 + (1-p)*b22
        # 整理得：p*(b11 - b21 - b12 + b22) = (b22 - b21)
        denominator2 = b11 - b21 - b12 + b22
        if abs(denominator2) < 1e-10:
            # 玩家2对玩家1的策略总是无差异，没有内点混合均衡
            return None
        
        p = (b22 - b21) / denominator2
        
        # === 5) 检查是否为内点混合均衡 ===
        if 0 < p < 1 and 0 < q < 1:
            # 计算期望收益（按 p、q 加权）
            expected_payoff1 = p * (q * a11 + (1-q) * a12) + (1-p) * (q * a21 + (1-q) * a22)
            expected_payoff2 = q * (p * b11 + (1-p) * b21) + (1-q) * (p * b12 + (1-p) * b22)
            
            return NashEquilibrium(
                is_pure=False,
                player1_strategy=(p, 1-p),
                player2_strategy=(q, 1-q),
                payoff1=expected_payoff1,
                payoff2=expected_payoff2,
                description=f"混合策略: p={p:.3f}, q={q:.3f}"
            )
        
        return None
    
    def find_all_nash_equilibria(self) -> List[NashEquilibrium]:
        """
        寻找所有纳什均衡（纯策略和混合策略）
        
        Returns:
            所有纳什均衡列表
        """
        equilibria = []
        
        # === 1) 先找纯策略均衡 ===
        pure_equilibria = self.find_pure_nash_equilibria()
        equilibria.extend(pure_equilibria)
        
        # === 2) 再尝试寻找混合策略均衡 ===
        mixed_equilibrium = self.find_mixed_nash_equilibrium()
        if mixed_equilibrium is not None:
            equilibria.append(mixed_equilibrium)
        
        return equilibria


def backward_induction_expected_payoff(
    stage2_games: List[StaticGame],
    nature_probabilities: List[float],
    player_index: int,
    selection_strategy: str = "pessimistic"
) -> float:
    """
    使用逆向归纳计算第二阶段的期望收益
    
    Args:
        stage2_games: 不同自然状态下的第二阶段博弈列表
        nature_probabilities: 自然状态的概率分布
        player_index: 玩家索引 (0 或 1)
        selection_strategy: 多重均衡下的选择策略 ("optimistic", "pessimistic", "average")
    
    Returns:
        玩家的期望收益
    """
    # === 1) 输入合法性检查 ===
    assert len(stage2_games) == len(nature_probabilities), "博弈数量必须与概率数量相同"
    assert abs(sum(nature_probabilities) - 1.0) < 1e-6, "概率之和必须为1"
    
    expected_payoff = 0.0
    
    # === 2) 遍历每个自然状态（报复等级） ===
    for game, prob in zip(stage2_games, nature_probabilities):
        # 计算当前状态下的均衡
        equilibria = game.find_all_nash_equilibria()
        
        if not equilibria:
            raise ValueError("第二阶段博弈没有纳什均衡")
        
        # 收集该玩家在“所有均衡”下的收益
        payoffs = []
        for eq in equilibria:
            payoffs.append(eq.payoff1 if player_index == 0 else eq.payoff2)
            
        # === 3) 多均衡时的收益选择策略 ===
        if selection_strategy == "optimistic":
            payoff = max(payoffs)
        elif selection_strategy == "pessimistic":
            payoff = min(payoffs)
        elif selection_strategy == "average":
            payoff = sum(payoffs) / len(payoffs)
        else:
            payoff = payoffs[0]  # 未知策略时默认取第一个
        
        # === 4) 按自然状态概率加权求期望 ===
        expected_payoff += prob * payoff
    
    return expected_payoff
