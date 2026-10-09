

import numpy as np
import matplotlib.pyplot as plt

p = 0.1
rd = np.random.normal
sigma = 0.015

def main():
    minp = 10000000.
    maxp = -100000000.
    for i in range(100):
        v = rd(p, sigma)
        minp = min(minp, v)
        maxp = max(maxp, v)
    print(minp, maxp)

if __name__ == "__main__":
    main()