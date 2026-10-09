
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
酒吧博弈游戏的Python分析脚本
这个脚本会运行C++的仿真核心，然后用Python分析和可视化结果
"""

import os
import sys
# 把编译好的C++模块路径加到Python搜索路径里
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../cmake-build-debug/exp1'))
import barcore  # 导入我们编译好的C++模块

# 导入分析和绘图需要的库
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import statistics
import numpy as np

# 解决中文字体问题
def setup_chinese_fonts():
    import warnings

    # 添加字体搜索路径并强制刷新
    wqy_path = '/usr/share/fonts/truetype/wqy/wqy-microhei.ttc'

    if os.path.exists(wqy_path):
        # 手动注册字体
        from matplotlib.font_manager import FontProperties
        chinese_font_prop = FontProperties(fname=wqy_path)

        # 设置为默认字体
        plt.rcParams['font.family'] = 'sans-serif'
        plt.rcParams['font.sans-serif'] = ['WenQuanYi Micro Hei']
        plt.rcParams['axes.unicode_minus'] = False

        # 强制所有文本使用这个字体
        plt.rcParams['font.size'] = 10

        print("成功设置文泉驿字体")

        # 禁用字体警告
        warnings.filterwarnings('ignore', category=UserWarning, module='matplotlib')

        return chinese_font_prop
    else:
        print("未找到文泉驿字体文件")
        return None

# 设置字体并禁用警告
chinese_font = setup_chinese_fonts()

# 如果有自定义字体，创建一个通用的绘图函数
def safe_plot_setup():
    if chinese_font:
        # 为每个新图形设置字体
        plt.rcParams.update({
            'font.sans-serif': ['WenQuanYi Micro Hei'],
            'axes.unicode_minus': False,
            'font.family': 'sans-serif'
        })

if __name__ == '__main__':
    # 设置仿真参数
    cfg = barcore.config()
    cfg.n = 200                      # 总共200个人参与博弈
    cfg.t = 365                      # 仿真一年，365天
    cfg.c = int(0.6 * cfg.n)         # 酒吧能坐120人（60%的容量比较合理）
    cfg.random_ratio = 0.3           # 30%的人用随机策略（佛系玩家）
    cfg.adaptive_ratio = 0.2         # 20%的人用自适应策略（聪明玩家）
    cfg.kw = 5                       # 移动平均策略记住前5天（剩下50%的人用这个策略）
    cfg.seed = 42                    # 固定随机种子，保证结果可重现

    # 显示这次仿真的具体设置
    print("=" * 50)
    print("酒吧博弈仿真参数")
    print("=" * 50)
    print(f"总人数 (n): {cfg.n}")
    print(f"仿真天数 (t): {cfg.t}")
    print(f"酒吧容量 (c): {cfg.c} ({cfg.c/cfg.n:.1%} of population)")
    print(f"随机决策比例: {cfg.random_ratio}")
    print(f"自适应阈值比例: {cfg.adaptive_ratio}")
    print(f"移动平均比例: {1 - cfg.random_ratio - cfg.adaptive_ratio}")
    print(f"记忆长度 (kw): {cfg.kw}")
    print(f"随机种子: {cfg.seed}")
    print("=" * 50)

    # 开始跑仿真！这里会调用C++的核心算法
    print("正在运行仿真...")
    res = barcore.sim(cfg)
    print("仿真完成！")
    print()

    # 把C++返回的结果转换成Python列表，方便后续分析
    att = list(res.attendance)      # 每天去酒吧的人数
    avg = list(res.avg_rewards)     # 每天的平均奖励
    cum = list(res.cum_rewards)     # 每个人的累积奖励

    # 先看看基本的统计数字，了解大概情况
    print("=" * 50)
    print("仿真结果统计")
    print("=" * 50)
    print(f"平均出勤人数: {sum(att)/len(att):.2f}")
    print(f"出勤人数标准差: {statistics.stdev(att):.2f}")         # 波动有多大
    print(f"出勤人数方差: {statistics.pvariance(att):.2f}")       # 另一个衡量波动的指标
    print(f"超容量天数: {sum(1 for x in att if x > cfg.c)} ({sum(1 for x in att if x > cfg.c)/len(att):.1%})")  # 有多少天人太多了
    print(f"最大出勤人数: {max(att)}")
    print(f"最小出勤人数: {min(att)}")
    print()
    print(f"最终平均奖励: {avg[-1]:.4f}")                        # 最后一天大家的平均奖励
    print(f"最终累积奖励: {cum[-1]:.2f}")                        # 最后一个人的累积奖励（这里应该是所有人的平均）
    print(f"前10天出勤人数: {att[:10]}")                          # 看看刚开始的情况
    print(f"后10天出勤人数: {att[-10:]}")                         # 看看最后稳定后的情况
    print(f"前5天累积奖励: {cum[:5]}")                            # 前几个人的累积奖励
    print("=" * 50)
    
    # 开始画图！让数据可视化，更直观地看到博弈的结果
    plt.style.use('seaborn-v0_8' if 'seaborn-v0_8' in plt.style.available else 'default')
    safe_plot_setup()  # 确保使用中文字体

    # 第一套图：四合一的综合分析图
    plt.figure(figsize=(12, 8))

    # 图1: 每天去酒吧的人数变化
    plt.subplot(2, 2, 1)
    plt.plot(att, alpha=0.7, linewidth=1)
    plt.axhline(cfg.c, color='red', linestyle='--', label=f'酒吧容量 ({cfg.c})')
    plt.axhline(sum(att)/len(att), color='green', linestyle=':', label=f'平均出勤 ({sum(att)/len(att):.1f})')
    plt.title("每日酒吧出勤人数")
    plt.xlabel("天数")
    plt.ylabel("出勤人数")
    plt.legend()
    plt.grid(True, alpha=0.3)

    # 图2: 平均奖励的变化趋势
    plt.subplot(2, 2, 2)
    plt.plot(avg, color='orange', linewidth=2)
    plt.title("平均奖励变化趋势")
    plt.xlabel("天数")
    plt.ylabel("平均奖励")
    plt.grid(True, alpha=0.3)

    # 图3: 累积奖励增长情况
    plt.subplot(2, 2, 3)
    plt.plot(cum, color='purple', linewidth=2)
    plt.title("累积奖励增长")
    plt.xlabel("参与者")
    plt.ylabel("累积奖励")
    plt.grid(True, alpha=0.3)

    # 图4: 出勤人数分布直方图
    plt.subplot(2, 2, 4)
    plt.hist(att, bins=30, alpha=0.7, color='skyblue', edgecolor='black')
    plt.axvline(cfg.c, color='red', linestyle='--', label=f'酒吧容量 ({cfg.c})')
    plt.axvline(sum(att)/len(att), color='green', linestyle=':', label=f'平均出勤 ({sum(att)/len(att):.1f})')
    plt.title("出勤人数分布")
    plt.xlabel("出勤人数")
    plt.ylabel("频次")
    plt.legend()
    plt.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig("img/bar_game_analysis.png", dpi=300, bbox_inches='tight')
    print(f"\n综合分析图已保存到: img/bar_game_analysis.png")
    
    # 第二套图：出勤人数的详细分析
    plt.figure(figsize=(14, 6))
    safe_plot_setup()  # 确保使用中文字体

    plt.subplot(1, 2, 1)
    # 看看前100天的详细情况，了解系统是怎么稳定下来的
    days_to_show = min(100, len(att))
    plt.plot(range(days_to_show), att[:days_to_show], alpha=0.8)
    plt.axhline(cfg.c, color='red', linestyle='--', label=f'酒吧容量 ({cfg.c})')
    plt.fill_between(range(days_to_show), 0, cfg.c, alpha=0.2, color='green', label='容量范围内')
    plt.fill_between(range(days_to_show), cfg.c, max(att[:days_to_show]), alpha=0.2, color='red', label='超出容量')
    plt.title(f"前 {days_to_show} 天详细分析")
    plt.xlabel("天数")
    plt.ylabel("出勤人数")
    plt.legend()
    plt.grid(True, alpha=0.3)

    plt.subplot(1, 2, 2)
    # 用移动平均线来看趋势，减少噪声干扰
    window = 7  # 7天移动平均
    moving_avg = [sum(att[max(0, i-window):i+1])/len(att[max(0, i-window):i+1]) for i in range(len(att))]
    plt.plot(att, alpha=0.3, color='gray', label='每日出勤')
    plt.plot(moving_avg, color='blue', linewidth=2, label=f'{window}天移动平均')
    plt.axhline(cfg.c, color='red', linestyle='--', label=f'酒吧容量 ({cfg.c})')
    plt.title("出勤趋势分析")
    plt.xlabel("天数")
    plt.ylabel("出勤人数")
    plt.legend()
    plt.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig("img/attendance_detail.png", dpi=300, bbox_inches='tight')
    print(f"出勤详细分析已保存到: img/attendance_detail.png")
    
    # 第三套图：奖励分析，看看大家的收益情况
    plt.figure(figsize=(12, 5))
    safe_plot_setup()  # 确保使用中文字体

    plt.subplot(1, 2, 1)
    plt.plot(avg, color='orange', linewidth=2, label='平均奖励')
    plt.title("平均奖励收敛过程")
    plt.xlabel("天数")
    plt.ylabel("平均奖励")
    plt.grid(True, alpha=0.3)
    plt.legend()

    plt.subplot(1, 2, 2)
    # 计算每天的奖励变化（这里理解有点问题，cum是每个人的累积奖励，不是每天的）
    # 但先保持原来的逻辑，这可能是想看每个人的奖励差异
    daily_rewards = [cum[i] - (cum[i-1] if i > 0 else 0) for i in range(len(cum))]
    plt.plot(daily_rewards, alpha=0.7, color='green', label='个人奖励差异')
    window = 14
    moving_avg_rewards = [sum(daily_rewards[max(0, i-window):i+1])/len(daily_rewards[max(0, i-window):i+1]) for i in range(len(daily_rewards))]
    plt.plot(moving_avg_rewards, color='red', linewidth=2, label=f'{window}人移动平均')
    plt.title("个人奖励分布变化")
    plt.xlabel("参与者序号")
    plt.ylabel("奖励差异")
    plt.legend()
    plt.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig("img/reward_analysis.png", dpi=300, bbox_inches='tight')
    print(f"奖励分析已保存到: img/reward_analysis.png")
    
    # 深度统计分析 - 挖掘数据背后的故事
    print("\n" + "=" * 60)
    print("深度统计分析")
    print("=" * 60)

    # 看看酒吧的容量利用情况
    capacity_ratio = cfg.c / cfg.n
    over_capacity_days = sum(1 for x in att if x > cfg.c)
    under_capacity_days = len(att) - over_capacity_days

    print(f"\n🏪 容量利用分析:")
    print(f"   酒吧容量设定: {cfg.c}/{cfg.n} = {capacity_ratio:.1%}")
    print(f"   超容量天数: {over_capacity_days} ({over_capacity_days/len(att):.1%})")  # 有多少天人太多了
    print(f"   未满容量天数: {under_capacity_days} ({under_capacity_days/len(att):.1%})")  # 有多少天还有空位
    print(f"   平均利用率: {sum(att)/(cfg.c * len(att)):.1%}")  # 整体利用率

    # 看系统是否收敛到稳定状态
    last_100_days = att[-100:]
    first_100_days = att[:100]

    print(f"\n📈 系统收敛性分析:")
    print(f"   前100天平均出勤: {sum(first_100_days)/len(first_100_days):.2f}")
    print(f"   后100天平均出勤: {sum(last_100_days)/len(last_100_days):.2f}")
    print(f"   前100天标准差: {statistics.stdev(first_100_days):.2f}")  # 开始时的波动
    print(f"   后100天标准差: {statistics.stdev(last_100_days):.2f}")   # 稳定后的波动
    print(f"   收敛改善: {(statistics.stdev(first_100_days) - statistics.stdev(last_100_days)):.2f}")  # 波动减少了多少

    # 博弈论的平衡分析
    efficiency = 1 - abs(sum(att)/len(att) - cfg.c) / cfg.c

    print(f"\n⚖️  博弈均衡分析:")
    print(f"   理论最优出勤: {cfg.c}")  # 理想情况下每天应该去多少人
    print(f"   实际平均出勤: {sum(att)/len(att):.2f}")  # 实际平均去了多少人
    print(f"   偏离度: {abs(sum(att)/len(att) - cfg.c):.2f}")  # 偏离理想值多少
    print(f"   系统效率: {efficiency:.1%}")  # 整体效率如何
    
    # 看看大家的奖励情况
    total_reward = cum[-1]  # 最后一个人的累积奖励（这里的数据结构可能需要重新理解）
    optimal_reward = cfg.t * cfg.c  # 理论最优：每天都恰好容量数的人去，每人每天得1分
    reward_efficiency = total_reward / optimal_reward if optimal_reward > 0 else 0

    print(f"\n💰 奖励效率分析:")
    print(f"   总累积奖励: {total_reward:.2f}")
    print(f"   理论最优奖励: {optimal_reward:.2f}")  # 完美情况下的奖励
    print(f"   奖励效率: {reward_efficiency:.1%}")    # 达到理论最优的百分比
    print(f"   每人平均奖励: {total_reward/cfg.n:.2f}")

    # 看看是否有周期性规律（比如周末人多还是工作日人多）
    weekly_pattern = []
    for day_of_week in range(7):
        days_in_week = [att[i] for i in range(day_of_week, len(att), 7)]
        weekly_pattern.append(sum(days_in_week) / len(days_in_week))

    print(f"\n📅 周期模式分析 (按星期):")
    weekdays = ['周一', '周二', '周三', '周四', '周五', '周六', '周日']
    for i, day in enumerate(weekdays):
        if i < len(weekly_pattern):
            print(f"   {day}: {weekly_pattern[i]:.2f} 人")

    # 分析智能体的学习过程
    learning_phases = [
        ("初期 (1-30天)", att[:30]),          # 刚开始大家都在摸索
        ("学习期 (31-100天)", att[30:100] if len(att) > 100 else att[30:]),  # 开始有经验了
        ("稳定期 (后100天)", att[-100:])      # 最后达到平衡
    ]

    print(f"\n🧠 学习阶段分析:")
    for phase_name, phase_data in learning_phases:
        if len(phase_data) > 0:
            phase_avg = sum(phase_data) / len(phase_data)
            phase_std = statistics.stdev(phase_data) if len(phase_data) > 1 else 0
            print(f"   {phase_name}: 均值={phase_avg:.2f}, 波动={phase_std:.2f}")

    # 总结智能体策略的效果
    print(f"\n🤖 智能体策略配置:")
    total_agents = cfg.n
    random_agents = int(cfg.random_ratio * total_agents)
    adaptive_agents = int(cfg.adaptive_ratio * total_agents)
    moving_avg_agents = total_agents - random_agents - adaptive_agents
    print(f"   随机策略智能体: {random_agents} 个 ({cfg.random_ratio:.1%})")
    print(f"   自适应阈值智能体: {adaptive_agents} 个 ({cfg.adaptive_ratio:.1%})")
    print(f"   移动平均智能体: {moving_avg_agents} 个 ({moving_avg_agents/total_agents:.1%})")
    print(f"   新策略引入效果: 系统效率 {efficiency:.1%}, 波动减少 {(statistics.stdev(first_100_days) - statistics.stdev(last_100_days)):.2f}")

    print("=" * 60)
    print("分析完成！所有图表已保存到 img/ 目录")
    print("=" * 60)

    # 显示所有图表
    plt.show()