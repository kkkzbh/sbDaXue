
#ifdef P3397

#include<iostream>

constexpr int size = 1000 + 10;

int a[size][size];
int d[size][size];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    int x1,y1;
    int x2,y2;
    for(int i = 1;i<=m;++i)
    {
        std::cin >> x1 >> y1 >> x2 >> y2;
        ++d[x1][y1];
        --d[x1][y2+1];
        --d[x2+1][y1];
        ++d[x2+1][y2+1];
    }
    for(int i = 1;i<=n;++i)
    {
        for(int j = 1;j<=n;++j)
        {
            a[i][j] = a[i][j-1] + a[i-1][j] - a[i-1][j-1] + d[i][j];
        }
    }
    for(int i = 1;i<=n;++i)
    {
        for(int j = 1;j<=n;++j)
        {
            std::cout << a[i][j] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}


#endif