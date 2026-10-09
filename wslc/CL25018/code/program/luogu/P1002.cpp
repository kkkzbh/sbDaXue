


#ifdef P1002

#include<iostream>

constexpr int size = 20 + 10;
long long g[size][size];

bool ishorse(int x,int y,int mx,int my)
{
    if(x == mx && y == my) return true;
    if(x == mx - 2 && y == my - 1) return true;
    if(x == mx - 1 && y == my - 2) return true;
    if(x == mx + 1 && y == my - 2) return true;
    if(x == mx + 2 && y == my - 1) return true;
    if((x == mx - 2 || x == mx + 2) && y == my + 1) return true;
    if((x == mx - 1 || x == mx + 1) && y == my + 2) return true;
    return false;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int bx,by;
    int mx,my;
    std::cin >> bx >> by;
    std::cin >> mx >> my;
    ++bx,++by,++mx,++my;
    g[0][1] = 1;
    for(int i = 1;i<=bx;++i)
    {
        for(int j = 1;j<=by;++j)
        {
            if(ishorse(i,j,mx,my)) g[i][j] = 0LL;
            else
                g[i][j] = g[i-1][j] + g[i][j-1];
        }
    }
    std::cout << g[bx][by];

    return 0;
}

#endif
