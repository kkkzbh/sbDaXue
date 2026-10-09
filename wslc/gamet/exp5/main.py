"""
动态囚徒困境博弈模拟系统
实验5：完全信息博弈的建模
"""

import numpy as np
from dynamic_game_ import DynamicPrisonersDilemma
from examples import get_example_scenario


def input_2x2_matrix(player_name: str, row_names: tuple, col_names: tuple) -> np.ndarray:
    """
    输入2x2收益矩阵
    
    Args:
        player_name: 玩家名称
        row_names: 行策略名称
        col_names: 列策略名称
    
    Returns:
        2x2 numpy数组
    """
    print(f"\n请输入{player_name}的收益矩阵:")
    matrix = np.zeros((2, 2))
    
    for i, row_name in enumerate(row_names):
        for j, col_name in enumerate(col_names):
            while True:
                try:
                    value = float(input(f"  当{player_name}选择'{row_name}'，对方选择'{col_name}'时的收益: "))
                    matrix[i, j] = value
                    break
                except ValueError:
                    print("  输入无效，请输入数字")
    
    return matrix


def input_stage2_games():
    """输入第二阶段的所有报复-对抗博弈"""
    print("\n" + "="*60)
    print("第二阶段: 报复-对抗博弈参数设置")
    print("="*60)
    print("\n说明:")
    print("- 坦白者策略: 对抗/不对抗")
    print("- 报复方策略: 报复/不报复")
    print("- 报复等级1-4，等级越高报复越重")
    print("- 假设黑社会报复等级与沉默方报复等级相反")
    
    retaliation_payoffs = {}
    
    for level in range(1, 5):
        print(f"\n{'='*50}")
        print(f"报复等级 {level}")
        print(f"{'='*50}")
        
        # 输入坦白者的收益矩阵
        confessor_payoffs = input_2x2_matrix(
            "坦白者",
            ("对抗", "不对抗"),
            ("报复", "不报复")
        )
        
        # 输入报复者的收益矩阵
        retaliator_payoffs = input_2x2_matrix(
            "报复方(黑社会/沉默方)",
            ("报复", "不报复"),
            ("对抗", "不对抗")
        )
        
        retaliation_payoffs[level] = (confessor_payoffs, retaliator_payoffs)
    
    # 输入警察对报复等级的信念
    print("\n" + "="*50)
    print("警察对报复等级的信念 (概率分布)")
    print("="*50)
    
    while True:
        nature_beliefs = []
        print("\n请输入警察认为各报复等级发生的概率:")
        total = 0
        for level in range(1, 5):
            while True:
                try:
                    prob = float(input(f"  报复等级{level}的概率: "))
                    if 0 <= prob <= 1:
                        nature_beliefs.append(prob)
                        total += prob
                        break
                    else:
                        print("  概率必须在0到1之间")
                except ValueError:
                    print("  输入无效，请输入数字")
        
        if abs(total - 1.0) < 1e-6:
            break
        else:
            print(f"\n错误: 概率之和为{total:.3f}，必须等于1.0，请重新输入")
    
    return retaliation_payoffs, nature_beliefs


def input_stage1_game():
    """输入第一阶段的坦白-沉默博弈"""
    print("\n" + "="*60)
    print("第一阶段: 坦白-沉默博弈参数设置")
    print("="*60)
    print("\n说明:")
    print("- 这是囚徒困境的基础刑期设置")
    print("- 不包括未来报复的影响（系统会自动考虑）")
    print("- 策略: 坦白/沉默")
    
    # 输入嫌疑犯1的收益矩阵
    suspect1_payoffs = input_2x2_matrix(
        "嫌疑犯1",
        ("坦白", "沉默"),
        ("坦白", "沉默")
    )
    
    # 输入嫌疑犯2的收益矩阵
    suspect2_payoffs = input_2x2_matrix(
        "嫌疑犯2",
        ("坦白", "沉默"),
        ("坦白", "沉默")
    )
    
    return suspect1_payoffs, suspect2_payoffs


def run_interactive_mode():
    """交互模式：用户输入所有参数"""
    print("\n" + "="*60)
    print("动态囚徒困境博弈模拟系统")
    print("实验5：完全信息博弈的建模")
    print("="*60)
    
    # 创建博弈实例
    game = DynamicPrisonersDilemma()
    
    # 输入第二阶段参数
    retaliation_payoffs, nature_beliefs = input_stage2_games()
    game.set_stage2_games(retaliation_payoffs, nature_beliefs)
    
    # 输入第一阶段参数
    suspect1_payoffs, suspect2_payoffs = input_stage1_game()
    game.set_stage1_base_payoffs(suspect1_payoffs, suspect2_payoffs)
    
    # 运行完整分析
    success = game.run_complete_analysis()
    
    return success


def run_example_mode(example_name: str = "default"):
    """示例模式：使用预设参数"""
    print("\n" + "="*60)
    print("动态囚徒困境博弈模拟系统 - 示例模式")
    print("="*60)
    
    # 获取示例场景
    scenario = get_example_scenario(example_name)
    
    print(f"\n使用示例场景: {scenario['name']}")
    print(f"描述: {scenario['description']}")
    
    # 创建博弈实例
    game = DynamicPrisonersDilemma()
    
    # 设置参数
    game.set_stage2_games(
        scenario['retaliation_payoffs'],
        scenario['nature_beliefs']
    )
    game.set_stage1_base_payoffs(
        scenario['suspect1_payoffs'],
        scenario['suspect2_payoffs']
    )
    
    # 运行完整分析
    success = game.run_complete_analysis()
    
    return success


def main():
    """主函数"""
    print("\n欢迎使用动态囚徒困境博弈模拟系统!")
    print("\n请选择运行模式:")
    print("1. 交互模式 - 手动输入所有参数")
    print("2. 示例模式 (警察成功) - 使用预设的成功案例")
    print("3. 示例模式 (警察失败) - 使用预设的失败案例")
    print("4. 示例模式 (混合策略) - 混合策略均衡案例")
    
    while True:
        choice = input("\n请输入选项 (1/2/3/4): ").strip()
        
        if choice == "1":
            run_interactive_mode()
            break
        elif choice == "2":
            run_example_mode("success")
            break
        elif choice == "3":
            run_example_mode("failure")
            break
        elif choice == "4":
            run_example_mode("mixed")
            break
        else:
            print("无效选项，请重新输入")


if __name__ == "__main__":
    main()
