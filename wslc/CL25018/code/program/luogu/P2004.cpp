

#include<iostream>
#include<array>
#include<algorithm>

constexpr int N{ 1000 + 2  };

std::array<std::array<int,N>,N> a;
int n,m,c;

long long sum(int x1,int y1,int x2,int y2)
{
    return a[x2][y2] - a[x1 - 1][y2] - a[x2][y1 - 1] + a[x1 - 1][y1 - 1];
}

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    std::cin >> n >> m >> c;
    for(int i{ 1 }; i <= n; ++i)
        for(int j{ 1 }; j <= m; ++j)
        {
            std::cin >> a[i][j];
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
    long long ans{ 1ll << 63 };
    int ai,aj;
    for(int i{ 1 },ci{ c }; ci <= n; ++i,++ci)
        for(int j{ 1 },cj{ c }; cj <= n; ++j,++cj)
            if(long long val = sum(i,j,ci,cj); val > ans)
            {
                ai = i;
                aj = j;
                ans = val;
            }
    std::cout << ai << ' ' << aj;

    return 0;
}