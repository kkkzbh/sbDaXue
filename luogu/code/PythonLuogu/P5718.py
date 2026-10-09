

n = int(input())
a = list(map(int, input().split()))
ans = a[0]

for v in a:
    ans = min(ans,v)

print(ans)