
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# 参数设置
p0 = 0.01  # 可接受质量水平
p1 = 0.05  # 拒绝质量水平
alpha = 0.05  # 第一类错误概率
beta = 0.10  # 第二类错误概率

# 计算决策边界
lnA = np.log(beta / (1 - alpha)) / np.log(p1 / p0)
lnB = np.log((1 - beta) / alpha) / np.log(p1 / p0)


# SPRT模拟函数
def sprt_simulation(p0, p1, lnA, lnB, true_p):
    n = 0
    sum_x = 0
    while True:
        n += 1
        x = np.random.rand() < true_p  # 模拟抽样
        sum_x += x
        lnL = sum_x * np.log(p1 / p0) + (n - sum_x) * np.log((1 - p1) / (1 - p0))

        if lnL >= lnA:
            return 'accept', n
        elif lnL <= lnB:
            return 'reject', n


# # 模拟不同真实次品率下的SPRT性能
# true_p_range = np.arange(0.05, 0.26, 0.01)
# num_simulations = 10000
# oc_curve = np.zeros(len(true_p_range))
# asn_curve = np.zeros(len(true_p_range))
#
# for i, true_p in enumerate(true_p_range):
#     decisions = []
#     sample_sizes = []
#
#     for _ in range(num_simulations):
#         decision, sample_size = sprt_simulation(p0, p1, lnA, lnB, true_p)
#         decisions.append(decision)
#         sample_sizes.append(sample_size)
#
#     oc_curve[i] = np.mean(np.array(decisions) == 'accept')
#     asn_curve[i] = np.mean(sample_sizes)
#
# # 绘制OC曲线
# plt.figure(figsize=(10, 6))
# plt.plot(true_p_range, oc_curve, 'b-', linewidth=2, label='OC曲线')
# plt.axvline(x=p0, color='r', linestyle='--', linewidth=1.5, label='p0')
# plt.axvline(x=p1, color='r', linestyle='--', linewidth=1.5, label='p1')
# plt.title('操作特性（OC）曲线', fontsize=14)
# plt.xlabel('真实次品率', fontsize=12)
# plt.ylabel('接受概率', fontsize=12)
# plt.legend(loc='best')
# plt.grid(True)
# plt.savefig('问题1_OC曲线.png', dpi=300)
# plt.show()
#
# # 绘制ASN曲线
# plt.figure(figsize=(10, 6))
# plt.plot(true_p_range, asn_curve, 'g-', linewidth=2, label='ASN曲线')
# plt.axvline(x=p0, color='r', linestyle='--', linewidth=1.5, label='p0')
# plt.axvline(x=p1, color='r', linestyle='--', linewidth=1.5, label='p1')
# plt.title('平均样本量（ASN）曲线', fontsize=14)
# plt.xlabel('真实次品率', fontsize=12)
# plt.ylabel('平均样本量', fontsize=12)
# plt.legend(loc='best')
# plt.grid(True)
# plt.savefig('问题1_ASN曲线.png', dpi=300)
# plt.show()
#
# # 计算在p0和p1处的具体性能指标
# idx_p0 = np.argmin(np.abs(true_p_range - p0))
# idx_p1 = np.argmin(np.abs(true_p_range - p1))
#
# p0_performance = [oc_curve[idx_p0], asn_curve[idx_p0]]
# p1_performance = [oc_curve[idx_p1], asn_curve[idx_p1]]
#
# # 输出结果
# print('SPRT模型性能指标：')
# print(f'在p0 ({p0}) 处的接受概率: {p0_performance[0]}')
# print(f'在p0 ({p0}) 处的平均样本量: {p0_performance[1]}')
# print(f'在p1 ({p1}) 处的接受概率: {p1_performance[0]}')
# print(f'在p1 ({p1}) 处的平均样本量: {p1_performance[1]}')
#
# # 保存结果到Excel文件
# results_df = pd.DataFrame({
#     '真实次品率': true_p_range,
#     '接受概率': oc_curve,
#     '平均样本量': asn_curve
# })
# results_df.to_excel('问题1_SPRT性能指标.xlsx', index=False)
#
# # 模拟实际检测过程
# num_batches = 1000
# batch_decisions = []
# batch_sample_sizes = []
#
# for _ in range(num_batches):
#     true_p = 0.10 + 0.05 * np.random.randn()  # 模拟批次间的质量波动
#     true_p = np.clip(true_p, 0, 1)  # 确保次品率在[0,1]范围内
#     decision, n = sprt_simulation(p0, p1, lnA, lnB, true_p)
#     batch_decisions.append(decision)
#     batch_sample_sizes.append(n)
#
# # 统计结果
# reject_rate = np.mean(np.array(batch_decisions) == 'reject')
# avg_sample_size = np.mean(batch_sample_sizes)
#
# # 输出实际检测结果
# print('实际检测结果：')
# print(f'拒收率: {reject_rate}')
# print(f'平均样本量: {avg_sample_size}')
#
# # 绘制样本量分布直方图
# plt.figure(figsize=(10, 6))
# plt.hist(batch_sample_sizes, bins=30, density=True)
# plt.title('样本量分布', fontsize=14)
# plt.xlabel('样本量', fontsize=12)
# plt.ylabel('频率', fontsize=12)
# plt.grid(True)
# plt.savefig('问题1_样本量分布.png', dpi=300)
# plt.show()
#
# # 保存实际检测结果到Excel文件
# actual_results_df = pd.DataFrame({
#     '样本量': batch_sample_sizes,
#     '决策': batch_decisions
# })
# actual_results_df.to_excel('问题1_实际检测结果.xlsx', index=False)


