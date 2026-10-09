

import numpy as np


# 零配件
class sap:
    l: list = []
    def __init__(self,buy_s,check_s,bad_p):
        self.buy_s = buy_s
        self.check_s = check_s
        self.bad_p = bad_p
        sap.l.append(self)

# 半成品
class lose:
    l: list = []
    def __init__(self,fit_s,check_s,bad_p,dis_s):
        self.buy_s = fit_s
        self.check_s = check_s
        self.bad_p = bad_p
        self.dis_s = dis_s
        sap.l.append(self)

# 成品
class fip:
    price = 0.
    fit_s = 0.
    check_s = 0.
    bad_p = 0.
    dis_s = 0.
    swap_s = 0.

class component:
    def __init__(self,index):
        self.i = index
        val = np.random.rand()
        if val < sap.l[i].bad_p:
            self.ok = False
        else:
            self.ok = True




if __name__ == '__main__':
    m,n = map(int,input("请输入工序m和零配件n 格式为:m n").split())
    make = [[0 for _ in range(n + 1)] for _ in range(m + 1)]
    print("请按矩阵形式输入参数 格式: 第i行为第i个零件每行为次品率p 购买单价s 检测成本c,")
    for i in range(n):
        p,s,c = map(float,input().split())
        sap(s,c,p)
    bn = int(input("请输入半成品个数"))
    print("按同样规则按格式输入 次品率p 装配成本s 检测成本c 拆解费用d")
    for i in range(bn):
        p,s,c,d = map(float,input().split())
        lose(s,c,p,d)
    print("一行输入各需要哪些上件")
    for i in range(bn):
        arr = list(map(int,input().split()))

    print("请按格式输入成品参数 次品率p 装配成本s 检测成本c 拆解费用d 调换损失x 市场售价price")
    fip.bad_p,fip.fit_s,fip.check_s,fip.dis_s,fip.swap_s,fip.price = map(float,input().split())


