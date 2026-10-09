
import math

m,t,s = map(int,input().split())
if t == 0:
    print(0)
else:
    sume = math.ceil(s / t)
    print(max(m - sume,0))