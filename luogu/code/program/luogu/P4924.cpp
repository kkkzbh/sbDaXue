

#ifdef P4924

#include<iostream>
#include<array>

constexpr int size = 500 + 2;
std::array<std::array<int,size>,size> matrix;

void trans(int x,int y,int r,int z)
{
    for(int i = x - r,m = y - r; i <= x + r;++i,++m)         //第 i - x + r 行(从第0行开始)
    {
        for(int j = y + i - x + 1,n = x + m - y + 1; j <= y + r;++j,++n)  //从第n行开始 列偏移n + 1;
        {
            std::swap(matrix[i][j],matrix[n][m]);
        }
    }
    if(z)
    {
        for(int a = x - r,b = x + r;a != b;++a,--b)
        {
            for(int i = y - r; i <= y + r;++i)
            {
                std::swap(matrix[a][i],matrix[b][i]);
            }
        }
    }
    else
    {
        for(int a = y - r,b = y + r;a != b;++a,--b)
        {
            for(int i = x - r; i <= x + r;++i)
            {
                std::swap(matrix[i][a],matrix[i][b]);
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    int tmp = 1;
    for(int i = 1;i<=n;++i)
    {
        for(int j = 1;j<=n;++j)
        {
            matrix[i][j] = tmp++;
        }
    }
    int x,y,r,z;
    for(int i = 1; i <= m; ++i)
    {
        std::cin >> x >> y >> r >> z;
        trans(x,y,r,z);
    }

    for(int i = 1;i<=n;++i)
    {
        for(int j = 1;j<=n;++j)
        {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}

#endif
