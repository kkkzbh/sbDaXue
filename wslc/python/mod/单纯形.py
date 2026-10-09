

import numpy as np
from fractions import Fraction as frac

def iteration(x:int, y:int, A):
    a[x] /= a[x][y]
    for i in filter(lambda i: i != x, range(len(a))):
        a[i] -= a[i][y] * a[x]

a = np.array([
    [frac(-1), frac(5), frac(0), frac(0), frac(0), frac(0)],
    [frac(0), frac(0), frac(0), frac(0), frac(-1), frac(0)],
    [frac(1), frac(2), frac(1), frac(0), frac(0), frac(8)],
    [frac(1), frac(-1), frac(0), frac(-1), frac(1), frac(4)]
])


a[1] += a[3]

iteration(3,0,a)

a = np.delete(a, 1, 0)
a = np.delete(a,4,1)

iteration(1,1,a)

a = np.vstack([a, np.array([0, 0, frac(-1, 3), frac(-1, 3), frac(-1, 3)], dtype=frac)])
a = np.hstack([a[:, :-1], np.array([[0], [0], [0], [1]], dtype=frac), a[:, -1:]])

iteration(3,2,a)

for i in range(len(a)):
    for j in range(len(a[0])):
        print(a[i][j], end = ' ' * (7 - len(str(a[i][j]))))
    print()