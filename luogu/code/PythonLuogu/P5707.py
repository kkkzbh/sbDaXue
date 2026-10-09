
import math

s,v = map(int,input().split())
time = int(math.ceil(s / v)) + 10

h = time // 60
time = time % 60
if time != 0:
    time = 60 - time;
    h += 1
h = (8 - h + 24) % 24
print(f"{h:02d}:{time:02d}")