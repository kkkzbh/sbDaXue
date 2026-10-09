

from typing import Callable
import matplotlib.pyplot as plt
import numpy as np
import sympy as sp

# 图解法

def solve1(Q: Callable[[float],int]) -> None:
    x = np.array(range(0,20 + 1))
    y = np.array([Q(_) for _ in x])

    plt.figure()
    plt.title("Profit function of live pig sale")
    plt.plot(x,y)
    plt.xlabel(R"selling time$(t)$")
    plt.xticks(x)
    plt.ylabel(R"profit$(Q)$",rotation = 90)

    index,value = max(enumerate(y),key = lambda tp: tp[1])
    print(f"解法1: 在{index}处取最大值{value}")

    plt.show()

# 代数法
def solve2() -> None:
    t,r,g = sp.symbols("t r g")
    Q = (8 - g * t) * (80 + r * t) - 4 * t - 640

    dQ = sp.diff(Q,t)
    res = sp.solve(dQ,t)

    rv = 2
    gv = 0.1

    kt = [_.evalf(subs = { r: rv,g: gv }) for _ in res]
    ans = [Q.evalf(subs = { t:_,r: rv,g: gv }) for _ in kt]

    print(f"解法2: 函数在{kt}处取得最大值{ans}")

def main():
    r: int = 2
    g: float = 0.1
    Q: Callable[[float],int] = lambda t:(8 - g * t) * (80 + r * t) - 4 * t - 640
#    solve1(Q)

    solve2()


if __name__ == '__main__':
    main()