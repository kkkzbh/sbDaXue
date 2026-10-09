

a,b,c,d = map(int,input().split())
hh,mm = (c - a),(d - b)
if mm < 0:
    hh -= 1
    mm += 60

print(hh,mm)



