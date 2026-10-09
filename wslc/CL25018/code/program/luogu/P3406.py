

n,m = map(int,input().split())

a = [0] * (m + 3)
tmp = list(map(int, input().split()))
for i in range(1,m + 1):
    a[i] = tmp[i - 1]

node = [(0,0,0)] * (n + 3)
for i in range(1,n):
    node[i] = tuple(map(int, input().split()))

diff = [0] * (n + 3)
for i in range(1,m):
    st = min(a[i],a[i + 1])
    ed = max(a[i],a[i + 1])
    diff[st] += 1
    diff[ed] -= 1
for i in range(1,n + 1):
    diff[i] += diff[i - 1]
ans = 0
for i in range(1,n):
    ans += min(diff[i] * node[i][0],diff[i] * node[i][1] + node[i][2])

print(ans)