
import math

h,r = map(int,input().split())
pi = 3.14
ans = math.ceil(20000 / (pi * r**2 * h))

print(ans)