#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
伯川德模型博弈模拟系统（修复版）
关键改进：
1. 修复了学习算法，使其能正确收敛到纳什均衡
2. 添加了最优响应计算
3. 改进了策略更新逻辑
"""

import sys
import argparse
import json
from typing import List, Tuple, Dict
import matplotlib.pyplot as plt
import matplotlib
# 修复中文显示问题
matplotlib.rcParams['font.sans-serif'] = ['SimHei', 'Microsoft YaHei', 'DejaVu Sans', 'Arial Unicode MS']
matplotlib.rcParams['axes.unicode_minus'] = False
matplotlib.rcParams['font.family'] = 'sans-serif'


class BertrandAgent:
    """伯川德博弈智能体（修复版）"""
    
    def __init__(self, agent_id: int, name: str, capacity: int, 
                 initial_threshold: float = 70.0, learning_rate: float = 0.2):
        """
        初始化智能体
        
        Args:
            agent_id: 智能体ID (1或2)
            name: 智能体名称
            capacity: 场地容量
            initial_threshold: 初始门槛
            learning_rate: 学习率 (0-1)
        """
        self.id = agent_id
        self.name = name
        self.capacity = capacity
        self.threshold = initial_threshold
        self.learning_rate = learning_rate
        
        # 历史数据
        self.history = {
            'thresholds': [],
            'payoffs': [],
            'students': []
        }
        
        # 学习参数
        self.optimal_threshold = 100 - capacity / 2  # 容量约束最优门槛
        self.last_payoff = 0
        self.last_threshold = initial_threshold
        self.last_opponent_threshold = None
        
        # 探索参数
        self.exploration_rate = 0.1  # 10%概率进行探索
        self.rounds_played = 0
        
    def choose_threshold(self, manual_value: float = None) -> float:
        """
        选择门槛策略
        
        Args:
            manual_value: 手动指定的门槛值
            
        Returns:
            门槛值
        """
        if manual_value is not None:
            self.threshold = max(0, min(100, manual_value))
        return self.threshold
    
    def calculate_best_response(self, opponent_threshold: float, 
                                total_students: int, r: float, c: float, 
                                lambda_penalty: float) -> float:
        """
        计算对手策略的最优响应
        
        策略分析：
        1. 如果我门槛略低于对手，我赢得全部市场
        2. 需要考虑容量约束，避免超容量
        3. 找到收益最大化的门槛
        
        Returns:
            最优响应门槛
        """
        # 情况1：如果对手门槛很高，我设置最优门槛即可
        if opponent_threshold > self.optimal_threshold + 10:
            return self.optimal_threshold
        
        # 情况2：如果对手门槛在我最优门槛附近或更低
        # 计算略低于对手的门槛能获得的收益
        undercut_threshold = max(0, opponent_threshold - 1)
        students_if_undercut = int(total_students * (100 - undercut_threshold) / 100)
        
        # 如果抢到的学生数不超容量，值得竞争
        if students_if_undercut <= self.capacity:
            # 收益 = (r - c) * students
            profit_if_undercut = (r - c) * students_if_undercut
            
            # 与不竞争相比（收益为0）
            if profit_if_undercut > 0:
                return undercut_threshold
        
        # 情况3：如果竞争会导致超容量，计算是否值得
        if students_if_undercut > self.capacity:
            # 计算超容量的收益（含惩罚）
            overcapacity = students_if_undercut - self.capacity
            penalty = (lambda_penalty / 2) * (overcapacity ** 2)
            profit_with_penalty = r * students_if_undercut - c * students_if_undercut - penalty
            
            # 如果仍然有正收益，可以考虑
            if profit_with_penalty > 100:  # 设置一个盈利阈值
                # 但要控制门槛，不要招太多学生
                # 找到恰好满容量的门槛
                optimal_students = self.capacity
                optimal_threshold_for_capacity = 100 - (optimal_students / total_students) * 100
                return max(0, min(optimal_threshold_for_capacity, opponent_threshold - 0.5))
            else:
                # 超容量收益不佳，退出竞争，设置高门槛
                return min(100, opponent_threshold + 5)
        
        # 默认返回最优门槛
        return self.optimal_threshold
    
    def update_strategy(self, payoff: float, opponent_threshold: float,
                       total_students: int, r: float, c: float, lambda_penalty: float):
        """
        根据上一轮结果更新策略（改进的学习机制）
        
        核心思想：
        1. 计算最优响应
        2. 逐步向最优响应靠拢
        3. 加入少量探索避免局部最优
        """
        self.rounds_played += 1
        
        # 记录历史
        self.history['thresholds'].append(self.threshold)
        self.history['payoffs'].append(payoff)
        
        # 首次博弈，不更新
        if self.last_opponent_threshold is None:
            self.last_payoff = payoff
            self.last_threshold = self.threshold
            self.last_opponent_threshold = opponent_threshold
            return
        
        # 计算最优响应
        best_response = self.calculate_best_response(
            opponent_threshold, total_students, r, c, lambda_penalty
        )
        
        # 策略更新：向最优响应方向移动
        adjustment = self.learning_rate * (best_response - self.threshold)
        
        # 如果收益在下降，加大调整幅度
        if payoff < self.last_payoff - 50:
            adjustment *= 1.5
        
        # 应用调整
        self.threshold += adjustment
        
        # 添加探索：偶尔尝试不同策略
        import random
        if random.random() < self.exploration_rate and self.rounds_played < 50:
            exploration = random.uniform(-3, 3)
            self.threshold += exploration
        
        # 限制范围
        self.threshold = max(0, min(100, self.threshold))
        
        # 更新记录
        self.last_payoff = payoff
        self.last_threshold = self.threshold
        self.last_opponent_threshold = opponent_threshold
    
    def __str__(self):
        return f"{self.name} (容量:{self.capacity}, 当前门槛:{self.threshold:.1f})"


class BertrandGame:
    """伯川德博弈系统"""
    
    def __init__(self, total_students: int = 200, 
                 revenue_per_student: float = 10.0,
                 cost_per_student: float = 3.0,
                 overcapacity_penalty: float = 8.0):
        """
        初始化博弈系统
        
        Args:
            total_students: 总学生数
            revenue_per_student: 每个学生的收益
            cost_per_student: 每个学生的基础成本
            overcapacity_penalty: 超容量惩罚系数
        """
        self.N = total_students
        self.r = revenue_per_student
        self.c = cost_per_student
        self.lambda_penalty = overcapacity_penalty
        
        # 创建智能体（降低初始学习率，提高稳定性）
        self.agent1 = BertrandAgent(1, "程序设计训练营", capacity=80, 
                                    initial_threshold=70, learning_rate=0.15)
        self.agent2 = BertrandAgent(2, "软创算法组", capacity=60, 
                                    initial_threshold=75, learning_rate=0.15)
        
        # 博弈历史
        self.game_history = []
        self.round_number = 0
    
    def demand(self, threshold: float) -> int:
        """
        需求函数：满足门槛的学生数
        
        Args:
            threshold: 门槛值
            
        Returns:
            学生数量
        """
        return int(self.N * (100 - threshold) / 100)
    
    def calculate_payoff(self, agent: BertrandAgent, students: int) -> float:
        """
        计算智能体收益
        
        Args:
            agent: 智能体
            students: 招收的学生数
            
        Returns:
            收益值
        """
        if students == 0:
            return 0
        
        # 基础收益
        revenue = self.r * students
        basic_cost = self.c * students
        
        # 超容量惩罚
        if students > agent.capacity:
            overcapacity = students - agent.capacity
            penalty = (self.lambda_penalty / 2) * (overcapacity ** 2)
            return revenue - basic_cost - penalty
        else:
            return revenue - basic_cost
    
    def play_round(self, threshold1: float = None, threshold2: float = None) -> Dict:
        """
        进行一轮博弈
        
        Args:
            threshold1: 智能体1的门槛 (None表示自动选择)
            threshold2: 智能体2的门槛 (None表示自动选择)
            
        Returns:
            本轮博弈结果
        """
        self.round_number += 1
        
        # 智能体选择策略
        t1 = self.agent1.choose_threshold(threshold1)
        t2 = self.agent2.choose_threshold(threshold2)
        
        # 计算学生分配
        if t1 < t2 - 0.01:  # 智能体1门槛更低，赢得市场
            students1 = self.demand(t1)
            students2 = 0
        elif t2 < t1 - 0.01:  # 智能体2门槛更低，赢得市场
            students1 = 0
            students2 = self.demand(t2)
        else:  # 门槛相等，平分市场
            total = self.demand(t1)
            students1 = total // 2
            students2 = total - students1
        
        # 计算收益
        payoff1 = self.calculate_payoff(self.agent1, students1)
        payoff2 = self.calculate_payoff(self.agent2, students2)
        
        # 记录结果
        result = {
            'round': self.round_number,
            'agent1_threshold': t1,
            'agent2_threshold': t2,
            'agent1_students': students1,
            'agent2_students': students2,
            'agent1_payoff': payoff1,
            'agent2_payoff': payoff2
        }
        
        self.game_history.append(result)
        self.agent1.history['students'].append(students1)
        self.agent2.history['students'].append(students2)
        
        # 智能体学习更新策略
        self.agent1.update_strategy(payoff1, t2, self.N, self.r, self.c, self.lambda_penalty)
        self.agent2.update_strategy(payoff2, t1, self.N, self.r, self.c, self.lambda_penalty)
        
        return result
    
    def print_result(self, result: Dict):
        """打印博弈结果"""
        print(f"\n{'='*70}")
        print(f"第 {result['round']} 轮博弈结果")
        print(f"{'='*70}")
        print(f"{'智能体':<20} {'门槛':>10} {'学生数':>10} {'收益':>15}")
        print(f"{'-'*70}")
        print(f"{self.agent1.name:<20} {result['agent1_threshold']:>10.2f} "
              f"{result['agent1_students']:>10} {result['agent1_payoff']:>15.2f}")
        print(f"{self.agent2.name:<20} {result['agent2_threshold']:>10.2f} "
              f"{result['agent2_students']:>10} {result['agent2_payoff']:>15.2f}")
        print(f"{'='*70}\n")
    
    def save_history(self, filename: str = "game_history.json"):
        """保存博弈历史到JSON文件"""
        with open(filename, 'w', encoding='utf-8') as f:
            json.dump(self.game_history, f, ensure_ascii=False, indent=2)
        print(f"博弈历史已保存到 {filename}")
    
    def plot_results(self):
        """绘制博弈结果折线图"""
        if not self.game_history:
            print("没有博弈数据可绘制！")
            return
        
        rounds = [r['round'] for r in self.game_history]
        
        # 创建图表
        fig, axes = plt.subplots(3, 1, figsize=(12, 10))
        fig.suptitle('伯川德博弈模拟结果', fontsize=16, fontweight='bold')
        
        # 子图1: 门槛变化
        ax1 = axes[0]
        ax1.plot(rounds, [r['agent1_threshold'] for r in self.game_history], 
                marker='o', label=self.agent1.name, linewidth=2, markersize=4)
        ax1.plot(rounds, [r['agent2_threshold'] for r in self.game_history], 
                marker='s', label=self.agent2.name, linewidth=2, markersize=4)
        ax1.axhline(y=60, color='r', linestyle='--', alpha=0.5, label='训练营最优门槛(60)')
        ax1.axhline(y=70, color='b', linestyle='--', alpha=0.5, label='算法组最优门槛(70)')
        ax1.set_xlabel('博弈轮次')
        ax1.set_ylabel('招生门槛')
        ax1.set_title('门槛策略演化')
        ax1.legend()
        ax1.grid(True, alpha=0.3)
        
        # 子图2: 学生数变化
        ax2 = axes[1]
        ax2.plot(rounds, [r['agent1_students'] for r in self.game_history], 
                marker='o', label=self.agent1.name, linewidth=2, markersize=4)
        ax2.plot(rounds, [r['agent2_students'] for r in self.game_history], 
                marker='s', label=self.agent2.name, linewidth=2, markersize=4)
        ax2.axhline(y=80, color='r', linestyle='--', alpha=0.5, label='训练营容量(80)')
        ax2.axhline(y=60, color='b', linestyle='--', alpha=0.5, label='算法组容量(60)')
        ax2.set_xlabel('博弈轮次')
        ax2.set_ylabel('招收学生数')
        ax2.set_title('招生人数演化')
        ax2.legend()
        ax2.grid(True, alpha=0.3)
        
        # 子图3: 收益变化
        ax3 = axes[2]
        ax3.plot(rounds, [r['agent1_payoff'] for r in self.game_history], 
                marker='o', label=self.agent1.name, linewidth=2, markersize=4)
        ax3.plot(rounds, [r['agent2_payoff'] for r in self.game_history], 
                marker='s', label=self.agent2.name, linewidth=2, markersize=4)
        ax3.axhline(y=560, color='r', linestyle='--', alpha=0.5, label='训练营理论均衡收益(560)')
        ax3.axhline(y=0, color='b', linestyle='--', alpha=0.5, label='算法组理论均衡收益(0)')
        ax3.set_xlabel('博弈轮次')
        ax3.set_ylabel('收益')
        ax3.set_title('收益演化')
        ax3.legend()
        ax3.grid(True, alpha=0.3)
        
        plt.tight_layout()
        plt.savefig('bertrand_game_results_fixed.png', dpi=300, bbox_inches='tight')
        print("图表已保存为 bertrand_game_results_fixed.png")
        plt.show()
    
    def analyze_convergence(self):
        """分析博弈是否收敛到纳什均衡"""
        if len(self.game_history) < 5:
            print("博弈轮次太少，无法分析收敛性")
            return
        
        # 取最后10轮的平均值
        last_n = min(10, len(self.game_history))
        last_rounds = self.game_history[-last_n:]
        avg_t1 = sum(r['agent1_threshold'] for r in last_rounds) / last_n
        avg_t2 = sum(r['agent2_threshold'] for r in last_rounds) / last_n
        avg_payoff1 = sum(r['agent1_payoff'] for r in last_rounds) / last_n
        avg_payoff2 = sum(r['agent2_payoff'] for r in last_rounds) / last_n
        
        print("\n" + "="*70)
        print(f"收敛性分析（最后{last_n}轮平均）")
        print("="*70)
        print(f"{'指标':<30} {'实际值':>15} {'理论均衡值':>15} {'误差':>10}")
        print("-"*70)
        print(f"训练营平均门槛 {avg_t1:>15.2f} {60:>15.2f} {abs(avg_t1-60):>10.2f}")
        print(f"算法组平均门槛 {avg_t2:>15.2f} {70:>15.2f} {abs(avg_t2-70):>10.2f}")
        print(f"训练营平均收益 {avg_payoff1:>15.2f} {560:>15.2f} {abs(avg_payoff1-560):>10.2f}")
        print(f"算法组平均收益 {avg_payoff2:>15.2f} {0:>15.2f} {abs(avg_payoff2-0):>10.2f}")
        print("="*70)
        
        # 判断是否收敛
        threshold_converged = abs(avg_t1 - 60) < 5 and abs(avg_t2 - 70) < 10
        payoff_converged = abs(avg_payoff1 - 560) < 100 and abs(avg_payoff2 - 0) < 50
        
        if threshold_converged and payoff_converged:
            print("\n✓ 博弈已基本收敛到纳什均衡")
            print("  训练营：门槛≈60，赢得市场，收益≈560")
            print("  算法组：门槛≈70，退出市场，收益≈0")
        else:
            print("\n⚠ 博弈尚未完全收敛，建议继续运行更多轮次")
            if not threshold_converged:
                print("  - 门槛策略仍在调整中")
            if not payoff_converged:
                print("  - 收益尚未稳定")


def interactive_mode(game: BertrandGame):
    """交互模式"""
    print("\n" + "="*70)
    print("伯川德博弈模拟系统 - 交互模式（修复版）")
    print("="*70)
    print("\n指令格式:")
    print("  auto <轮数> - 自动博弈指定轮数")
    print("  q          - 退出并绘制结果")
    print("\n示例: auto 100")
    print("="*70 + "\n")
    
    while True:
        try:
            command = input(f"第 {game.round_number + 1} 轮 > ").strip()
            
            if not command:
                continue
            
            if command.lower() == 'q':
                break
            
            parts = command.split()
            
            if parts[0] == 'auto' and len(parts) == 2:
                rounds = int(parts[1])
                print(f"\n开始自动博弈 {rounds} 轮...")
                for i in range(rounds):
                    result = game.play_round()
                    if i == rounds - 1 or (i + 1) % 20 == 0:  # 每20轮打印一次
                        game.print_result(result)
                continue
            else:
                print("⚠ 无效指令，请使用 'auto <轮数>' 或 'q'")
                
        except ValueError:
            print("⚠ 输入格式错误")
        except KeyboardInterrupt:
            print("\n\n中断博弈...")
            break
    
    # 保存和分析
    if game.game_history:
        game.save_history()
        game.analyze_convergence()
        game.plot_results()


def main():
    parser = argparse.ArgumentParser(
        description='伯川德博弈模拟系统（修复版）',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog='''
示例:
  交互模式:
    python bertrand_game_fixed.py
    然后输入: auto 150
        ''')
    
    args = parser.parse_args()
    
    # 创建博弈系统
    game = BertrandGame()
    
    print("\n" + "="*70)
    print("理论分析")
    print("="*70)
    print("训练营容量：80，最优门槛：60")
    print("算法组容量：60，最优门槛：70")
    print("\n预期纳什均衡：")
    print("  - 训练营设置门槛60，赢得全部80名学生，收益560")
    print("  - 算法组设置门槛70，无学生报名，收益0")
    print("="*70 + "\n")
    
    interactive_mode(game)


if __name__ == "__main__":
    main()