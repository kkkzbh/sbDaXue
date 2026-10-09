

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

p = 0.1
sigma = 0.015
rd = lambda p: np.random.normal(p,sigma)
class Package:
    def __init__(self, bad, cost, dect):
        self.bad = bad
        self.cost = cost
        self.dect = dect

class Result:
    def __init__(self, bad, cost, dect, sell):
        self.bad = bad
        self.cost = cost
        self.dect = dect
        self.sell = sell

x = []
dic = {

}
def lowestcost(cases, z1, z2, z3, r, s):
    costs = float('inf')
    choose = -1
    for i in range(16):
        x1 = Package(z1.bad, z1.cost, z1.dect)
        x2 = Package(z2.bad, z2.cost, z2.dect)
        x3 = Result(z3.bad, z3.cost, z3.dect, z3.sell)
        c1, c2, c3, c4 = cases[i]
        n = 100
        #零件的成本
        costpackage = (x1.cost + x2.cost) * n
        nr = min(n * (1 - (1 - c1) * x1.bad), n * (1 - (1 - c2) * x2.bad))
        nr0 = nr
        #检测费用与组装费用
        costdect = (x1.dect * c1 + x2.dect * c2) * n + nr * x3.dect
        costcombin = nr * x3.cost
        x3.bad = 1 - (1 - x3.bad) * (1 - (1 - c1) * x1.bad) * (1 - (1 - c2) * x2.bad)
        #调换损失
        costchange = r * nr * x3.bad * (1 - c3)
        nr0 -= nr * x3.bad * (1 - c3)
        #拆解费用
        costapart = c4 * nr * x3.bad * s
        x1.bad = x1.bad / x3.bad
        x2.bad = x2.bad / x3.bad
        n = c4 * nr * x3.bad
        nr = min(n * (1 - (1 - c1) * x1.bad), n * (1 - (1 - c2) * x2.bad))
        x3.bad = 1 - (1 - x3.bad) * (1 - (1 - c1) * x1.bad) * (1 - (1 - c2) * x2.bad)
        #拆解后再次进行加工引起的成本
        costapart += (x1.dect * c1 + x2.dect * c2) * n + nr * x3.dect + nr * x3.cost + r * nr * x3.bad * (1 - c3)
        nr0 -= nr * x3.bad * (1 - c3)
        nr0 += nr
        #总成本减去总营销额
        costall = costpackage + costdect + costcombin + costchange + costapart - nr0 * x3.sell
        x.append(costall)
        print(costall,end = ' ')
        if costall < costs:
            costs = costall
            choose = i
    print()
    return choose

cases = [[0, 0, 0, 0], [0, 0, 0, 1], [0, 0, 1, 0], [0, 0, 1, 1], [0, 1, 0, 0], [0, 1, 0, 1], [0, 1, 1, 0], [0, 1, 1, 1], [1, 0, 0, 0], [1, 0, 0, 1], [1, 0, 1, 0], [1, 0, 1, 1], [1, 1, 0, 0], [1, 1, 0, 1], [1, 1, 1, 0], [1, 1, 1, 1]]

ans = []
y1 = Package(rd(0.1), 4, 2)
y2 = Package(rd(0.1), 18, 3)
y3 = Result(rd(0.1), 6, 3, 56)
r = 6
s = 5
ans.append(lowestcost(cases, y1, y2, y3, r, s))
x.append(f"选择方案{ans[0]}")
dic["情况1利润"] = x
x = []

y1 = Package(rd(0.2), 4, 2)
y2 = Package(rd(0.2), 18, 3)
y3 = Result(rd(0.2), 6, 3, 56)
ans.append(lowestcost(cases, y1, y2, y3, r, s))
x.append(f"选择方案{ans[1]}")
dic["情况2利润"] = x
x = []

y1 = Package(rd(0.1), 4, 2)
y2 = Package(rd(0.1), 18, 3)
y3 = Result(rd(0.1), 6, 3, 56)
r = 30
ans.append(lowestcost(cases, y1, y2, y3, r, s))
x.append(f"选择方案{ans[2]}")
dic["情况3利润"] = x
x = []

y1 = Package(rd(0.2), 4, 1)
y2 = Package(rd(0.2), 18, 1)
y3 = Result(rd(0.2), 6, 2, 56)
ans.append(lowestcost(cases, y1, y2, y3, r, s))
x.append(f"选择方案{ans[3]}")
dic["情况4利润"] = x
x = []

y1 = Package(rd(0.1), 4, 8)
y2 = Package(rd(0.2), 18, 1)
y3 = Result(rd(0.1), 6, 2, 56)
r = 10
ans.append(lowestcost(cases, y1, y2, y3, r, s))
x.append(f"选择方案{ans[4]}")
dic["情况5利润"] = x
x = []

y1 = Package(rd(0.05), 4, 2)
y2 = Package(rd(0.05), 18, 3)
y3 = Result(rd(0.05), 6, 3, 56)
r = 10
s = 40
ans.append(lowestcost(cases, y1, y2, y3, r, s))
x.append(f"选择方案{ans[5]}")
dic["情况6利润"] = x
x = []

for i in range(len(ans)):
    print(ans[i])

df = pd.DataFrame.from_dict(dic)

df.to_excel("问题4(1)策略结果.xlsx",index = False)
