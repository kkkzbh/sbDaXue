"""
示例场景
提供预设的博弈参数用于测试和演示
"""

import numpy as np
from typing import Dict


def get_example_scenario(name: str) -> Dict:
    """
    获取示例场景
    
    Args:
        name: 场景名称 ("success", "failure", "mixed", "default")
    
    Returns:
        包含所有博弈参数的字典
    """
    scenarios = {
        "success": create_success_scenario(),
        "failure": create_failure_scenario(),
        "mixed": create_mixed_strategy_scenario(),
        "default": create_success_scenario(),
    }
    
    if name not in scenarios:
        raise ValueError(f"未知场景: {name}。可用场景: {list(scenarios.keys())}")
    
    return scenarios[name]


def create_success_scenario() -> Dict:
    """
    创建警察成功的场景
    
    在这个场景中，囚徒困境的设置使得至少有一个嫌疑犯选择坦白是纳什均衡
    """
    # 第二阶段: 报复-对抗博弈
    # 坦白者的策略: 对抗/不对抗 (行)
    # 报复方的策略: 报复/不报复 (列)
    
    retaliation_payoffs = {}
    
    # 报复等级1 (轻微报复 - 黑社会报复轻，沉默方报复重)
    # 坦白者面对轻微的黑社会报复，但沉默方报复较重
    retaliation_payoffs[1] = (
        np.array([[-2, 0],    # 坦白者: 对抗时(报复, 不报复), 不对抗时(报复, 不报复)
                  [-3, 0]]),
        np.array([[1, -1],    # 报复方: (对抗, 不对抗) 当选择报复时, (对抗, 不对抗) 当选择不报复时
                  [0, 0]])
    )
    
    # 报复等级2
    retaliation_payoffs[2] = (
        np.array([[-3, 0],
                  [-4, 0]]),
        np.array([[2, -1],
                  [0, 0]])
    )
    
    # 报复等级3
    retaliation_payoffs[3] = (
        np.array([[-4, 0],
                  [-5, 0]]),
        np.array([[2, 0],
                  [0, 0]])
    )
    
    # 报复等级4 (严重报复 - 黑社会报复重，沉默方报复轻)
    retaliation_payoffs[4] = (
        np.array([[-5, 0],
                  [-6, 0]]),
        np.array([[3, 0],
                  [0, 0]])
    )
    
    # 警察的信念 (均匀分布)
    nature_beliefs = [0.25, 0.25, 0.25, 0.25]
    
    # 第一阶段: 坦白-沉默博弈 (经典囚徒困境)
    # 收益解释: 负数表示刑期（越大越差）
    # (坦白,坦白): 各判5年
    # (坦白,沉默): 坦白者释放，沉默者判10年
    # (沉默,坦白): 沉默者判10年，坦白者释放
    # (沉默,沉默): 各判1年（只能以较轻罪名起诉）
    
    suspect1_payoffs = np.array([
        [-5, 0],    # 坦白时: (对方坦白, 对方沉默)
        [-10, -1]   # 沉默时: (对方坦白, 对方沉默)
    ])
    
    suspect2_payoffs = np.array([
        [-5, -10],  # 对方坦白时: (自己坦白, 自己沉默)
        [0, -1]     # 对方沉默时: (自己坦白, 自己沉默)
    ])
    
    return {
        "name": "警察成功场景",
        "description": "经典囚徒困境设置，坦白是占优策略",
        "retaliation_payoffs": retaliation_payoffs,
        "nature_beliefs": nature_beliefs,
        "suspect1_payoffs": suspect1_payoffs,
        "suspect2_payoffs": suspect2_payoffs
    }


def create_failure_scenario() -> Dict:
    """
    创建警察失败的场景
    
    在这个场景中，由于未来报复的影响过大，两个嫌疑犯都选择沉默
    """
    # 第二阶段: 报复非常严重
    retaliation_payoffs = {}
    
    for level in range(1, 5):
        # 报复的收益很高，对抗的代价很大
        retaliation_payoffs[level] = (
            np.array([[-10 - level*2, -5],    # 坦白者
                      [-15 - level*2, -8]]),
            np.array([[5 + level, 2],          # 报复方
                      [0, 0]])
        )
    
    # 警察倾向于认为高等级报复更可能
    nature_beliefs = [0.1, 0.2, 0.3, 0.4]
    
    # 第一阶段: 刑期差距不够大
    suspect1_payoffs = np.array([
        [-3, 0],
        [-4, -1]
    ])
    
    suspect2_payoffs = np.array([
        [-3, -4],
        [0, -1]
    ])
    
    return {
        "name": "警察失败场景",
        "description": "报复后果严重，抵消了坦白的刑期优势，两人都选择沉默",
        "retaliation_payoffs": retaliation_payoffs,
        "nature_beliefs": nature_beliefs,
        "suspect1_payoffs": suspect1_payoffs,
        "suspect2_payoffs": suspect2_payoffs
    }


def create_mixed_strategy_scenario() -> Dict:
    """
    创建混合策略均衡的场景
    
    设计收益使得纯策略均衡不存在，只有混合策略均衡
    """
    # 第二阶段: 匹配博弈类型
    retaliation_payoffs = {}
    
    for level in range(1, 5):
        # 类似猜硬币博弈的结构
        retaliation_payoffs[level] = (
            np.array([[2, -1],     # 坦白者
                      [-1, 2]]),
            np.array([[-2, 1],     # 报复方
                      [1, -2]])
        )
    
    nature_beliefs = [0.25, 0.25, 0.25, 0.25]
    
    # 第一阶段: 设计成类似性别战的结构
    # 双方都坦白或都沉默时收益较高，但偏好不同
    suspect1_payoffs = np.array([
        [-2, -5],
        [-5, -1]
    ])
    
    suspect2_payoffs = np.array([
        [-2, -5],
        [-5, -1]
    ])
    
    return {
        "name": "混合策略场景",
        "description": "收益设置使得存在混合策略纳什均衡",
        "retaliation_payoffs": retaliation_payoffs,
        "nature_beliefs": nature_beliefs,
        "suspect1_payoffs": suspect1_payoffs,
        "suspect2_payoffs": suspect2_payoffs
    }


# 用于快速测试的函数
def test_all_scenarios():
    """测试所有预设场景"""
    from dynamic_game_ import DynamicPrisonersDilemma
    
    for scenario_name in ["success", "failure", "mixed"]:
        print(f"\n{'#'*60}")
        print(f"# 测试场景: {scenario_name}")
        print(f"{'#'*60}")
        
        scenario = get_example_scenario(scenario_name)
        
        game = DynamicPrisonersDilemma()
        game.set_stage2_games(
            scenario['retaliation_payoffs'],
            scenario['nature_beliefs']
        )
        game.set_stage1_base_payoffs(
            scenario['suspect1_payoffs'],
            scenario['suspect2_payoffs']
        )
        
        success = game.run_complete_analysis()
        print(f"\n场景 '{scenario_name}' 警察是否成功: {'是' if success else '否'}")


if __name__ == "__main__":
    test_all_scenarios()
