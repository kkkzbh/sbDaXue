"""
讲解重点函数:
1) updateBeliefs(): 将 GUI 输入的四个报复等级“信念”归一化，并触发重算。
2) updateSettings(): 更新黑社会强度/逆向规则/均衡选择策略，并触发重算。
3) updatePrisonYears(): 更新第一阶段刑期参数，并触发重算。
4) findOptimalStrategy(): 粗略搜索“坦白/沉默”刑期阈值，使警察至少成功一次。
5) run_logic(): 核心计算流程（生成第二阶段、设置第一阶段、求均衡）。
6) recalculate(): 汇总结果，重建调整矩阵，并发送给 QML 展示。
"""

import sys
import json
import numpy as np
from PySide6.QtCore import QObject, Slot, Signal, Property
from dynamic_game_ import DynamicPrisonersDilemma

class GameController(QObject):
    # Signals to update UI
    # matrixDataJson: Includes matrices for all levels and stage 1, plus equilibrium info
    matrixDataChanged = Signal(str) 
    
    # Text summary of results
    resultSummaryChanged = Signal(str)

    def __init__(self):
        super().__init__()
        # 创建动态博弈模型实例（后续所有计算都由它完成）
        self.game = DynamicPrisonersDilemma()
        
        # === 默认参数（GUI 启动时的初始值）===
        self._probabilities = [0.25, 0.25, 0.25, 0.25]
        self._gang_damage = 2.0
        self._inverse_rule = True
        
        # === 第一阶段刑期（囚徒困境）===
        # 约定：收益 = -刑期（刑期越大收益越小）
        self._y_cc = 5.0  # Both Confess (Defect/Defect) => 5 years
        self._y_cd = 0.0  # Me Confess (Defect), You Silent (Coop) => 0 years
        self._y_dc = 10.0 # Me Silent (Coop), You Confess (Defect) => 10 years
        self._y_dd = 1.0  # Both Silent (Coop/Coop) => 1 year
        
        # === 多重均衡时的选择策略（保守/乐观/平均）===
        self._selection_strategy = "pessimistic"
        
        # 启动时立即计算一次，把结果送到界面
        self.recalculate()

    @Slot(float, float, float, float)
    def updateBeliefs(self, p1, p2, p3, p4):
        # === 步骤1：汇总用户输入的四个滑条数值 ===
        total = p1 + p2 + p3 + p4

        # === 步骤2：做概率归一化（防止和不为 1）===
        if total == 0:
            # 用户把四个概率全拉到 0 时，回退到均匀分布
            self._probabilities = [0.25, 0.25, 0.25, 0.25]
        else:
            # 按总和归一化，确保 sum = 1
            self._probabilities = [p1/total, p2/total, p3/total, p4/total]

        # === 步骤3：触发整套模型重算 ===
        self.recalculate()

    @Slot(float, bool, str)
    def updateSettings(self, gang_damage_base, inverse_rule, strategy):
        # === 步骤1：更新报复强度参数 ===
        self._gang_damage = gang_damage_base

        # === 步骤2：更新“逆向规则”开关 ===
        # True 代表“沉默方报复等级与黑社会相反”
        self._inverse_rule = inverse_rule

        # === 步骤3：更新多均衡下的收益选择策略 ===
        self._selection_strategy = strategy

        # === 步骤4：触发重算 ===
        self.recalculate()

    @Slot(float, float, float, float)
    def updatePrisonYears(self, cc, cd, dc, dd):
        """
        Update years. 
        cc: Both Confess
        cd: I Confess, You Silent
        dc: I Silent, You Confess
        dd: Both Silent
        """
        # === 步骤1：更新四个刑期参数 ===
        # cc: 双方坦白；cd: 自己坦白对方沉默
        # dc: 自己沉默对方坦白；dd: 双方沉默
        self._y_cc = cc
        self._y_cd = cd
        self._y_dc = dc
        self._y_dd = dd

        # === 步骤2：触发重算 ===
        self.recalculate()
        
    @Slot()
    def findOptimalStrategy(self):
        """
        Try to find the minimum years reduction needed for confession (cd) to make at least one person confess.
        We fix other parameters and vary _y_cd.
        """
        # === 保存原始参数，搜索结束后可以恢复 ===
        original_cd = self._y_cd
        
        # Search range: 0 to 10 years (or up to dc)
        # We want to find a value X for 'Confess-Silent' (Reward) such that success is True.
        # Usually, lowering prison time (higher payoff) encourages confession.
        # Currently _y_cd is 0 (best). If it's failing at 0, we can't do much better unless we give negative years (money reward).
        # But maybe the current setting is failing?
        # Let's search for the "Threshold" where it switches from Fail to Success.
        
        found = False
        optimal_val = -1.0
        
        # === 从“较严厉”往“更优待”逐步试探 ===
        # 这里用 10 → -5 的步进搜索，模拟“逐步给更多好处”
        for val in np.arange(10.0, -5.5, -0.5):
            # 暂时替换“坦白/沉默”的刑期
            self._y_cd = float(val)

            # 只跑核心逻辑，判断是否成功（不触发 UI 更新）
            self.run_logic()

            # 如果已经满足“至少有人坦白”，认为达到了可行阈值
            if self.success:
                found = True
                optimal_val = val
                break
                
        # === 恢复或固定最优值 ===
        self._y_cd = optimal_cd = optimal_val if found else original_cd
        
        # === 给界面一个文本反馈 ===
        if found:
            self.resultSummaryChanged.emit(
                f"Optimization: Found threshold at {optimal_val} years for Confess/Silent."
            )
        else:
            self.resultSummaryChanged.emit(
                "Optimization: Could not find a working strategy in range [-5, 10]."
            )
            self._y_cd = original_cd
             
        self.recalculate()

    def run_logic(self):
        # === 第一步：生成第二阶段“报复-对抗”博弈 ===
        # 输入：黑社会强度 + 是否启用逆向规则
        retaliation_payoffs = self.game.generate_retaliation_games(
            self._gang_damage, self._inverse_rule
        )

        # 把 4 个等级的博弈矩阵 + 警察信念分布写入模型
        self.game.set_stage2_games(retaliation_payoffs, self._probabilities)

        # === 第二步：构造第一阶段“坦白-沉默”基础收益矩阵 ===
        # 规则：收益 = -刑期（刑期越短收益越高）
        p1_payoffs = np.array([
            [-self._y_cc, -self._y_cd],  # 玩家1选择“坦白”
            [-self._y_dc, -self._y_dd]   # 玩家1选择“沉默”
        ])

        # 玩家2对称构造（注意列表示玩家2的选择）
        p2_payoffs = np.array([
            [-self._y_cc, -self._y_dc],  # 玩家1坦白时，玩家2的收益
            [-self._y_cd, -self._y_dd]   # 玩家1沉默时，玩家2的收益
        ])

        # 把第一阶段基础收益写入模型
        self.game.set_stage1_base_payoffs(p1_payoffs, p2_payoffs)

        # === 第三步：求解第二阶段所有报复等级下的纳什均衡 ===
        # 结果会保存在 self.game.stage2_equilibria
        self.game.solve_stage2()

        # === 第四步：逆向归纳，求第一阶段均衡 ===
        # 内部会：计算第二阶段期望收益 → 调整第一阶段矩阵 → 求纳什均衡
        self.game.solve_stage1_with_backward_induction(self._selection_strategy)

    def recalculate(self):
        # === 1) 先跑核心逻辑，得到最新的均衡与期望收益 ===
        self.run_logic()
        
        # === 2) 收集第二阶段数据，用于 QML 矩阵展示 ===
        s2_data = {}
        for level, game in self.game.retaliation_games.items():
            eq_coords = []
            for eq in self.game.stage2_equilibria.get(level, []):
                if eq.is_pure:
                    # pure strategy is (0/1, 0/1)
                    # if p1 uses strategy 0 (prob 1.0) -> index 0
                    r = 0 if eq.player1_strategy[0] > 0.5 else 1
                    c = 0 if eq.player2_strategy[0] > 0.5 else 1
                    eq_coords.append([r, c])
            
            s2_data[level] = {
                 "p1": game.player1_payoffs.tolist(),
                 "p2": game.player2_payoffs.tolist(),
                 "eqCoords": eq_coords
            }
            
        # === 3) 第一阶段（调整后）矩阵 ===
        # 说明：dynamic_game_ 内部生成了调整后的矩阵，但没有保存。
        # 这里按相同逻辑重建，以便前端可视化。
        
        # 先算第二阶段的期望收益（坦白者 / 报复者）
        conf_fut, ret_fut = self.game.calculate_expected_stage2_payoffs(
            self._selection_strategy
        )
        
        # 重新构建基础矩阵（先用刑期，后加上期望收益）
        s1_adj_p1 = np.array([[-self._y_cc, -self._y_cd], [-self._y_dc, -self._y_dd]])
        s1_adj_p2 = np.array([[-self._y_cc, -self._y_dc], [-self._y_cd, -self._y_dd]])
        
        # === 将第二阶段期望收益贴回第一阶段 ===
        # [0,0]: 双方坦白 → 两人都承担“坦白者”的未来期望收益
        s1_adj_p1[0,0] += conf_fut
        s1_adj_p2[0,0] += conf_fut
        
        # [0,1]: 玩家1坦白、玩家2沉默
        s1_adj_p1[0,1] += conf_fut
        s1_adj_p2[0,1] += ret_fut
        
        # [1,0]: 玩家1沉默、玩家2坦白
        s1_adj_p1[1,0] += ret_fut
        s1_adj_p2[1,0] += conf_fut
        
        # === 4) 依据第一阶段均衡判断警察成败 ===
        success = self.game.check_police_success()
        self.success = success
        
        # === 5) 收集第一阶段“纯策略均衡”坐标用于高亮 ===
        s1_eq_coords = []
        for eq in self.game.stage1_equilibria:
            if eq.is_pure:
                r = 0 if eq.player1_strategy[0] > 0.5 else 1
                c = 0 if eq.player2_strategy[0] > 0.5 else 1
                s1_eq_coords.append([r, c])

        # === 6) 打包 JSON，发送给 QML ===
        payload = {
            "stage2": s2_data,
            "stage1": {
                "p1": s1_adj_p1.tolist(),
                "p2": s1_adj_p2.tolist(),
                "eqCoords": s1_eq_coords,
                "confessor_future": conf_fut,
                "retaliator_future": ret_fut
            },
            "success": success
        }
        
        # 发出信号：矩阵数据（可视化）+ 结果摘要（文本）
        self.matrixDataChanged.emit(json.dumps(payload))
        self.resultSummaryChanged.emit(f"Police Strategy: {'SUCCESS' if success else 'FAILURE'}\nConfessor Future Exp: {conf_fut:.2f}")

