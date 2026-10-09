"""
动态博弈模型
实现囚徒困境的两阶段动态博弈

讲解重点函数:
1) generate_retaliation_games(): 参数化生成第二阶段 4 个报复等级的收益矩阵。
2) set_stage2_games(): 把第二阶段矩阵与信念分布写入模型。
3) solve_stage2(): 对每个报复等级求静态博弈纳什均衡。
4) calculate_expected_stage2_payoffs(): 按信念分布计算第二阶段期望收益。
5) solve_stage1_with_backward_induction(): 逆向归纳调整第一阶段收益并求均衡。
6) check_police_success(): 根据均衡判断警察是否成功。
7) run_complete_analysis(): 串起完整分析流程。
"""

import numpy as np
from typing import List, Tuple, Dict
from game_theory_ import StaticGame, NashEquilibrium, backward_induction_expected_payoff


class DynamicPrisonersDilemma:
    """
    动态囚徒困境博弈
    
    博弈结构:
    1. 第一阶段: 两个嫌疑犯选择坦白或沉默
    2. 自然选择: 黑社会组织决定报复等级 (1-4级)
    3. 第二阶段: 坦白者面对报复，选择对抗或不对抗
    """
    
    def __init__(self):
        # 第二阶段博弈参数
        self.retaliation_games: Dict[int, StaticGame] = {}  # 不同报复等级下的博弈
        self.nature_beliefs: List[float] = []  # 警察对报复等级的信念
        
        # 第一阶段博弈参数
        self.stage1_base_payoffs = None  # 基础收益（不考虑未来）
        
        # 均衡结果
        self.stage2_equilibria: Dict[int, List[NashEquilibrium]] = {}
        self.stage1_equilibria: List[NashEquilibrium] = []
    
    @staticmethod
    def generate_retaliation_games(gang_base_damage: float = 2.0, 
                                 inverse: bool = True) -> Dict[int, Tuple[np.ndarray, np.ndarray]]:
        """
        参数化生成第二阶段的报复-对抗博弈矩阵
        
        Args:
            gang_base_damage: 黑社会报复基准伤害
            inverse: 是否应用“逆向规则”（沉默方报复等级与黑社会相反）
            
        Returns:
            retaliation_payoffs 字典
        """
        retaliation_payoffs = {}
        for level in range(1, 5):
            # === 1) 计算黑社会报复伤害 ===
            # 等级越高，伤害越重；这里用线性放大 + 0.5 缩放系数
            gang_damage = gang_base_damage * level * 0.5
            
            # === 2) 计算沉默方报复收益（心理满足）===
            # inverse=True：沉默方报复等级与黑社会相反（等级越低越“想报复”）
            if inverse:
                partner_level = 5 - level
                retaliation_benefit = 1.0 * partner_level * 0.5
            else:
                retaliation_benefit = 1.0 * level * 0.5
                
            # === 3) 初始化收益矩阵 ===
            # 行玩家 = 坦白者（对抗/不对抗）
            # 列玩家 = 报复方（报复/不报复）
            confessor_payoffs = np.zeros((2, 2))
            retaliator_payoffs = np.zeros((2, 2))
            
            # 策略: 0=对抗/报复, 1=不对抗/不报复
            
            # === 4) 填充 4 个策略组合的收益 ===
            # [对抗, 报复]: 双方冲突
            # 坦白者：伤害被对抗抵消一部分（*0.7），另加对抗成本 -0.5
            # 报复者：付出报复成本（-1.0）
            confessor_payoffs[0, 0] = -gang_damage * 0.7 - 0.5
            retaliator_payoffs[0, 0] = -1.0
            
            # [对抗, 不报复]: 虚惊一场
            # 坦白者只承担对抗成本；报复方不报复，收益 0
            confessor_payoffs[0, 1] = -0.5
            retaliator_payoffs[0, 1] = 0.0
            
            # [不对抗, 报复]: 承受全部伤害
            # 坦白者承受完整报复伤害；报复方获得心理满足收益
            confessor_payoffs[1, 0] = -gang_damage
            retaliator_payoffs[1, 0] = retaliation_benefit
            
            # [不对抗, 不报复]: 相安无事
            confessor_payoffs[1, 1] = 0.0
            retaliator_payoffs[1, 1] = 0.0
            
            # === 5) 保存该等级的矩阵 ===
            retaliation_payoffs[level] = (confessor_payoffs, retaliator_payoffs)
            
        return retaliation_payoffs
    
    def set_stage2_games(self, 
                        retaliation_payoffs: Dict[int, Tuple[np.ndarray, np.ndarray]],
                        nature_beliefs: List[float]):
        """
        设置第二阶段的报复-对抗博弈
        
        Args:
            retaliation_payoffs: 字典，键为报复等级(1-4)，值为(坦白者收益矩阵, 黑社会/沉默方收益矩阵)
            nature_beliefs: 警察对不同报复等级的信念分布 [P(等级1), P(等级2), P(等级3), P(等级4)]
        """
        # === 1) 基本合法性检查 ===
        assert len(retaliation_payoffs) == 4, "必须提供4个报复等级的收益矩阵"
        assert len(nature_beliefs) == 4, "必须提供4个报复等级的概率"
        assert abs(sum(nature_beliefs) - 1.0) < 1e-6, "概率之和必须为1"
        
        # === 2) 记录警察对自然状态的信念分布 ===
        self.nature_beliefs = nature_beliefs
        
        for level in range(1, 5):
            if level not in retaliation_payoffs:
                raise ValueError(f"缺少报复等级{level}的收益矩阵")
            
            confessor_payoffs, retaliator_payoffs = retaliation_payoffs[level]
            
            # === 3) 为每个等级创建一个 StaticGame ===
            # 统一使用“对抗/不对抗”“报复/不报复”作为策略名称，便于展示
            game = StaticGame(
                player1_payoffs=confessor_payoffs,
                player2_payoffs=retaliator_payoffs,
                strategy1_names=("对抗", "不对抗"),
                strategy2_names=("报复", "不报复")
            )
            
            # === 4) 缓存到字典中，便于后续求均衡 ===
            self.retaliation_games[level] = game
    
    def set_stage1_base_payoffs(self, 
                                suspect1_payoffs: np.ndarray,
                                suspect2_payoffs: np.ndarray):
        """
        设置第一阶段的基础收益（不考虑未来报复）
        
        Args:
            suspect1_payoffs: 嫌疑犯1的收益矩阵 (2x2)
            suspect2_payoffs: 嫌疑犯2的收益矩阵 (2x2)
            
        策略: 0=坦白, 1=沉默
        """
        # === 保存第一阶段基础收益矩阵 ===
        # 注意：这里不包含未来报复收益，后续会在逆向归纳时再叠加
        self.stage1_base_payoffs = (suspect1_payoffs, suspect2_payoffs)
    
    def solve_stage2(self) -> Dict[int, List[NashEquilibrium]]:
        """
        求解第二阶段所有报复等级下的纳什均衡
        
        Returns:
            字典，键为报复等级，值为该等级下的纳什均衡列表
        """
        # === 打印分析标题（方便在终端观察）===
        print("\n" + "="*60)
        print("第二阶段分析: 报复-对抗博弈")
        print("="*60)
        
        for level in range(1, 5):
            game = self.retaliation_games[level]
            # === 逐等级显示对应的收益矩阵 ===
            print(f"\n报复等级 {level} (概率: {self.nature_beliefs[level-1]:.2f})")
            game.display_payoff_matrix()
            
            # === 计算该静态博弈的所有纳什均衡（纯 + 混合）===
            equilibria = game.find_all_nash_equilibria()
            self.stage2_equilibria[level] = equilibria
            
            # === 输出均衡结果（便于课堂展示）===
            print(f"\n纳什均衡:")
            if equilibria:
                for eq in equilibria:
                    print(f"  - {eq}")
            else:
                print("  未找到纳什均衡")
        
        return self.stage2_equilibria
    
    def calculate_expected_stage2_payoffs(self, selection_strategy: str = "pessimistic") -> Tuple[float, float]:
        """
        计算第二阶段的期望收益
        
        Args:
            selection_strategy: 均衡选择策略 ("optimistic", "pessimistic", "average")
            
        Returns:
            (坦白者的期望收益, 报复方的期望收益)
        """
        # === 1) 按等级顺序收集 4 个静态博弈 ===
        games = [self.retaliation_games[i] for i in range(1, 5)]
        
        # === 2) 计算“坦白者”在第二阶段的期望收益 ===
        # 关键点：多重均衡时按 selection_strategy 选收益
        confessor_expected = backward_induction_expected_payoff(
            games, self.nature_beliefs, player_index=0, selection_strategy=selection_strategy
        )

        # === 3) 计算“报复方/沉默方”的期望收益 ===
        retaliator_expected = backward_induction_expected_payoff(
            games, self.nature_beliefs, player_index=1, selection_strategy=selection_strategy
        )
        
        return confessor_expected, retaliator_expected
    
    def solve_stage1_with_backward_induction(self, selection_strategy: str = "pessimistic") -> List[NashEquilibrium]:
        """
        使用逆向归纳求解第一阶段博弈
        
        Args:
            selection_strategy: 均衡选择策略
            
        Returns:
            第一阶段的纳什均衡列表
        """
        # === 1) 打印标题 ===
        print("\n" + "="*60)
        print("第一阶段分析: 坦白-沉默博弈 (考虑未来期望收益)")
        print("="*60)
        
        # === 2) 先计算第二阶段期望收益（作为“未来收益/损失”回贴第一阶段）===
        confessor_future, retaliator_future = self.calculate_expected_stage2_payoffs(selection_strategy)
        
        print(f"\n第二阶段期望收益:")
        print(f"  坦白者的期望收益: {confessor_future:.2f}")
        print(f"  (沉默方作为)报复者的期望收益: {retaliator_future:.2f}")
        
        # === 3) 读取第一阶段基础矩阵，并复制一份做“调整矩阵” ===
        suspect1_base, suspect2_base = self.stage1_base_payoffs
        
        # 创建调整后的收益矩阵
        # 策略索引说明:
        # [0,0]=双方坦白
        # [0,1]=嫌疑犯1坦白、嫌疑犯2沉默
        # [1,0]=嫌疑犯1沉默、嫌疑犯2坦白
        # [1,1]=双方沉默
        suspect1_adjusted = suspect1_base.copy()
        suspect2_adjusted = suspect2_base.copy()

        # === 4) 把第二阶段期望收益贴回第一阶段 ===
        # [0,0]: 双方坦白
        # 逻辑：两人都作为“坦白者”，都要承担未来被报复的期望损失
        suspect1_adjusted[0, 0] += confessor_future
        suspect2_adjusted[0, 0] += confessor_future
        
        # [0,1]: 嫌疑犯1坦白，嫌疑犯2沉默
        # 嫌疑犯1 → 坦白者期望收益
        # 嫌疑犯2 → 报复者期望收益
        suspect1_adjusted[0, 1] += confessor_future
        suspect2_adjusted[0, 1] += retaliator_future
        
        # [1,0]: 嫌疑犯1沉默，嫌疑犯2坦白
        # 嫌疑犯1 → 报复者期望收益
        # 嫌疑犯2 → 坦白者期望收益
        suspect1_adjusted[1, 0] += retaliator_future
        suspect2_adjusted[1, 0] += confessor_future
        
        # === 5) 用调整后的矩阵构建第一阶段静态博弈 ===
        stage1_game = StaticGame(
            player1_payoffs=suspect1_adjusted,
            player2_payoffs=suspect2_adjusted,
            strategy1_names=("坦白", "沉默"),
            strategy2_names=("坦白", "沉默")
        )
        
        print("\n调整后的第一阶段收益矩阵:")
        stage1_game.display_payoff_matrix()
        
        # === 6) 求第一阶段纳什均衡 ===
        self.stage1_equilibria = stage1_game.find_all_nash_equilibria()
        
        print(f"\n第一阶段纳什均衡:")
        if self.stage1_equilibria:
            for eq in self.stage1_equilibria:
                print(f"  - {eq}")
        else:
            print("  未找到纳什均衡")
        
        return self.stage1_equilibria
    
    def check_police_success(self) -> bool:
        """
        检查警察的策略是否成功（至少有一个嫌疑犯坦白）
        
        Returns:
            True 如果至少有一个嫌疑犯坦白，False 否则
        """
        # === 打印评估标题 ===
        print("\n" + "="*60)
        print("警察策略评估")
        print("="*60)
        
        if not self.stage1_equilibria:
            print("\n结果: ❌ 失败 - 第一阶段没有找到均衡")
            return False
        
        # === 遍历所有第一阶段均衡 ===
        for eq in self.stage1_equilibria:
            # 纯策略均衡
            if eq.is_pure:
                # 纯策略：看双方是否至少有人选择“坦白”
                # 约定：player_strategy = (1, 0) 表示策略1（坦白）
                #       player_strategy = (0, 1) 表示策略2（沉默）
                suspect1_confesses = eq.player1_strategy[0] == 1.0
                suspect2_confesses = eq.player2_strategy[0] == 1.0
                
                if suspect1_confesses or suspect2_confesses:
                    print(f"\n结果: ✓ 成功")
                    print(f"均衡策略: {eq.description}")
                    if suspect1_confesses and suspect2_confesses:
                        print("两个嫌疑犯都选择坦白")
                    elif suspect1_confesses:
                        print("嫌疑犯1选择坦白，嫌疑犯2选择沉默")
                    else:
                        print("嫌疑犯1选择沉默，嫌疑犯2选择坦白")
                    return True
            else:
                # 混合策略：只要坦白概率 > 0，就认为“可能坦白”
                suspect1_confess_prob = eq.player1_strategy[0]
                suspect2_confess_prob = eq.player2_strategy[0]
                
                if suspect1_confess_prob > 0 or suspect2_confess_prob > 0:
                    print(f"\n结果: ✓ 成功 (混合策略均衡)")
                    print(f"嫌疑犯1坦白概率: {suspect1_confess_prob:.2%}")
                    print(f"嫌疑犯2坦白概率: {suspect2_confess_prob:.2%}")
                    return True
        
        # 如果所有均衡都显示“沉默”，警察失败
        print(f"\n结果: ❌ 失败")
        print("所有均衡中，两个嫌疑犯都选择沉默")
        return False
    
    def run_complete_analysis(self):
        """运行完整的博弈分析"""
        # === 总控流程：按“第二阶段 → 第一阶段 → 成功评估”顺序执行 ===
        print("\n" + "="*60)
        print("动态囚徒困境博弈 - 完整分析")
        print("="*60)
        
        # 1) 第二阶段：求每个报复等级的静态博弈均衡
        self.solve_stage2()
        
        # 2) 第一阶段：逆向归纳后求均衡
        self.solve_stage1_with_backward_induction()
        
        # 3) 判断警察是否成功
        success = self.check_police_success()
        
        return success
