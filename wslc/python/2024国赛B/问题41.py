import numpy as np
import time
import matplotlib.pyplot as plt

np.random.seed(int(time.time()))

# 假设原件个数为 使用0表示不合格 1表示合格
total_cnt = 1000;  # 总数
i_cnt = 100;  # 次品数
a = np.array([0] * i_cnt + [1] * (total_cnt - i_cnt))
np.random.shuffle(a)  # 打乱
p0 = 0.1  # 二项分布概率
z1 = 1.65  # (1)的信度要求对应的正太值
z2 = 1.29

min_ex_cnt = 100  # 最少抽取次数
max_ex_cnt = 100  # 最多抽取个数
test_cnt = 100  # 单次测试次数


def test1(cnt: int) -> bool:
    c0, c1 = 0, 0
    for k in range(cnt):
        sec = np.random.randint(0, a.size)
        if a[sec] == 0:
            c0 += 1
        else:
            c1 += 1
    p = c0 / (c0 + c1)
    z = (p - p0) / np.sqrt(p0 * (1 - p0) / cnt)
    # print(f"抽取{cnt}个样本")
    # print(f"共有{c1}个合格品,{c0}个不合格品")
    # print(f"样本次品率为{p}")
    # print(f"计算的z值为{z},预期的z1为{z1}")
    if z >= z1:
        # print(f"因为{z} >= {z1},故拒绝")
        return False
    # print(f"因为{z} < {z1},故接受")
    return True


def test2(cnt: int) -> bool:
    c0, c1 = 0, 0
    for k in range(cnt):
        sec = np.random.randint(0, a.size)
        if a[sec] == 0:
            c0 += 1
        else:
            c1 += 1
    p = c0 / (c0 + c1)
    z = (p - p0) / np.sqrt(p0 * (1 - p0) / cnt)
    # print(f"抽取{cnt}个样本")
    # print(f"共有{c1}个合格品,{c0}个不合格品")
    # print(f"样本次品率为{p}")
    # print(f"计算的z值为{z},预期的z2为{z2}")
    if z >= z2:
        #    print(f"因为{z} >= {z2},故拒绝")
        return False
    # print(f"因为{z} < {z2},故接受")
    return True


x = [i for i in range(min_ex_cnt, max_ex_cnt + 1, 10)]
y = []

if __name__ == '__main__':

    xx = []
    yy = []

    for i in range(1,100 + 1):
        ok = 0
        for j in range(test_cnt):
            if test1(i):
                ok += 1
        xx.append(j)
        yy.append(ok / test_cnt)
        y.append(ok / test_cnt)
    plt.plot(xx, yy)
    plt.xlabel("Extraction number")
    plt.ylabel("success probability")
    print(y)
    print(x)
    plt.show()

