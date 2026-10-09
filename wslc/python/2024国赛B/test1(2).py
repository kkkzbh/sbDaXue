import numpy as np
from scipy.stats import binomtest
import matplotlib.pyplot as plt

p0 = 0.1
p1 = 0.15
a = 0.10
# 不妨认为第二类错误概率β与α相同
b = 0.10

# 似然函数的边界
ceil, floor = np.log((1 - b) / a), np.log(b / (1 - a))


# 定义似然函数(对数化)
def L(x, n):
    return x * np.log(p1 / p0) + (n - x) * np.log((1 - p1) / (1 - p0))


total = 10000
Z_95 = 1.65
# 使用无限公式计算的
n1 = int(((Z_95 ** 2) * p0 * (1 - p0)) / (a ** 2))
# 有限调整
n2 = int(n1 / (1 + (n1 - 1) / total))

print("无限公式n =", n1, "有限个体优化计算后n =", n2)


def extract(cnt: int) -> int:
    c0 = 0
    for i in range(cnt):
        sec = np.random.randint(0, data.size)
        if data[sec] == 0:
            c0 += 1
    return c0


def main() -> (bool,int):
    # 定义单次抽取的步长
    dc = 5

    c0, cnt = 0, 0
    if io:
        print(f"似然边界为{floor} ~ {ceil}")
    while cnt + dc <= 9999999999:
        c0 += extract(dc)
        cnt += dc
        lv = L(c0, cnt)
        if io:
            print(f"{cnt}里有次品{c0},样本次品率{c0 / cnt},似然值为{lv}")
        if lv <= floor:
            if io:
                print(f"抽{cnt},次品{c0},接受这批零件")
            return True,cnt
        elif lv >= ceil:
            if io:
                print(f"抽{cnt},次品{c0},拒绝这批零件")
            return False,cnt
    if cnt < n2:
        c0 += extract(n2 - cnt)
        cnt = n2
    p = c0 / cnt
    res = binomtest(c0, cnt, p0, alternative="less")
    ret = False
    if res.pvalue > a:
        if io:
            print("抽完，但是接受这批零件")
        ret = True,cnt
    else:
        if io:
            print("抽完，但是拒绝这批零件")
    if io:
        print(f"{cnt}里有次品{c0},样本次品率{p},可能性概率为{res.pvalue}")
    return ret,cnt


if __name__ == "__main__":
    pz = 0.10
    pz_start = 0.01
    pz_end = 0.40

    OCx = []
    OCy = []

    ASNx = []
    ASNy = []

    io = False
    pi = pz_start;
    while pi < pz_end:
        data = np.array([0] * int(pi * total) + [1] * int((1 - pi) * total))
        np.random.shuffle(data)

        OCx.append(pi)
        ASNx.append(pi)

        ok = 0
        s = 0

        for i in range(100):
            flag,cnt = main()
            if flag:
                ok += 1
            s += cnt

        OCy.append(ok / 100)
        ASNy.append(s / 100)

        pi += 0.03

    plt.title("operating characteristic curve")
    plt.xlabel("true sample probability p0")
    plt.ylabel("probability of acceptance p1")
    plt.yticks(ticks = np.arange(0, 1 + 0.05, 0.05))
    plt.plot(OCx, OCy)
    plt.axvline(p0, color = 'r', linestyle = "--")
    plt.axvline(p1, color = 'r', linestyle = "--")

    plt.figure()
    plt.title("Average sample size curve")
    plt.xlabel("true sample probability p0")
    plt.ylabel("average sample number")
    #plt.yticks([v for v in range(0,500,10)])
    plt.axvline(p0, color = 'r', linestyle = "--")
    plt.axvline(p1, color = 'r', linestyle = "--")
    plt.plot(ASNx, ASNy,color = "#B8860B")

    plt.show()
