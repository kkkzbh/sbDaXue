

#ifdef P2670

#include<iostream>

constexpr int size = 100 + 10;
char a[size][size];

int find(int x,int y)
{
    int count = 0;
    for(int i = x-1;i<=x+1;++i)
    {
        for(int j = y-1;j<=y+1;++j)
        {
            if(a[i][j] == '*') ++count;
        }
    }
    return count;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    for(int i = 1;i<=n;++i)
    {
        for(int j = 1;j<=m;++j)
        {
            std::cin >> a[i][j];
        }
    }
    for(int i = 1;i<=n;++i)
    {
        for(int j = 1;j<=m;++j)
        {
            if(a[i][j] == '*') std::cout << '*';
            else std::cout << find(i,j);
        }
        std::cout << '\n';
    }


    return 0;
}

#endif
