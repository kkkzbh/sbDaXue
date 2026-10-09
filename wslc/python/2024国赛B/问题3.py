import numpy as np
from sklearn.tree import DecisionTreeRegressor, export_text

# 情境数据: 每种情境下的零配件和成品的次品率、成本等
scenarios = [
    [0.10, 0.10, 0.10, 2, 3, 3, 6, 56, 6, 5],
    [0.20, 0.20, 0.20, 2, 3, 3, 6, 56, 6, 5],
    [0.10, 0.10, 0.10, 2, 3, 3, 6, 56, 6, 5],
    [0.20, 0.20, 0.20, 2, 3, 3, 6, 56, 30, 5],
    [0.10, 0.20, 0.10, 8, 3, 3, 6, 56, 10, 5],
    [0.05, 0.05, 0.05, 2, 3, 3, 6, 56, 10, 40]
]

# 决策组合矩阵 [检测零配件1, 检测零配件2, 检测成品, 拆解不合格成品]
X = np.array([
    [1, 1, 1, 1], [1, 1, 1, 0], [1, 1, 0, 1], [1, 1, 0, 0],
    [1, 0, 1, 1], [1, 0, 1, 0], [1, 0, 0, 1], [1, 0, 0, 0],
    [0, 1, 1, 1], [0, 1, 1, 0], [0, 1, 0, 1], [0, 1, 0, 0],
    [0, 0, 1, 1], [0, 0, 1, 0], [0, 0, 0, 1], [0, 0, 0, 0]
])

# 定义每个情境下不同决策组合对应的收益或损失
y = []

# 计算每个决策组合的收益或成本
for scenario in scenarios:
    defective_rate1, defective_rate2, defective_rate_final, \
        cost_check_part1, cost_check_part2, cost_check_final, \
        cost_assembly, market_price, exchange_loss, disassembly_cost = scenario

    scenario_y = []
    for decision in X:
        # 决策组合: [检测零配件1, 检测零配件2, 检测成品, 拆解不合格成品]
        check_part1, check_part2, check_final, disassemble = decision

        # 初步收益/成本计算逻辑
        revenue = market_price * (1 - defective_rate_final)
        total_cost = cost_assembly

        if check_part1:
            total_cost += cost_check_part1
            revenue -= defective_rate1 * market_price
        if check_part2:
            total_cost += cost_check_part2
            revenue -= defective_rate2 * market_price
        if check_final:
            total_cost += cost_check_final
            revenue -= defective_rate_final * market_price

        # 拆解成本或调换损失
        if disassemble:
            total_cost += disassembly_cost
        else:
            total_cost += exchange_loss

        # 最终收益或损失
        profit = revenue - total_cost
        scenario_y.append(profit)

    y.append(scenario_y)

# 将每个情境的决策结果展开为一维数组
y = np.array(y)

# 训练决策树回归模型，只用情境1进行训练 (为了示例)
clf = DecisionTreeRegressor(random_state=42)
clf.fit(X, y[0])  # 对应第一个情境的数据进行训练

# 输出决策树的规则
tree_rules = export_text(clf, feature_names=['检测零配件1', '检测零配件2', '检测成品', '拆解不合格成品'])
print(tree_rules)

# 找到每个情境下的最优决策组合
optimal_decisions = []
for i, scenario_y in enumerate(y):
    max_profit_index = np.argmax(scenario_y)
    optimal_decision = X[max_profit_index]
    optimal_profit = scenario_y[max_profit_index]
    optimal_decisions.append((optimal_decision, optimal_profit))
    print(f"情境 {i + 1} 最优决策: {optimal_decision}，预期收益: {optimal_profit}")

# 输出所有情境的最优决策
for i, (decision, profit) in enumerate(optimal_decisions):
    decision_desc = f"情境 {i + 1} 最优决策: 检测零配件1={decision[0]}, 检测零配件2={decision[1]}, 检测成品={decision[2]}, 拆解不合格成品={decision[3]}，预期收益: {profit:.2f}"
    print(decision_desc)
