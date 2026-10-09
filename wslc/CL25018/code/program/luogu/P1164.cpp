

#ifdef P1164

#include<iostream>
#include<algorithm>
constexpr int size = 100 + 10;
constexpr int money = 10000 + 10;

int dp[money][size]{};

int main()
{
    int n, m;
    std::cin >> n >> m;
    int cost[size]{};
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> cost[i];
    }
    for(int i = 0; i <= m;++i)
    {
        for(int j = 0; j <= n;++j)
        {
            if(i == 0 && j != 0) dp[i][j] = 1;
            else if(j == 1)
            {
                if(i == cost[j]) dp[i][j] = 1;
                else dp[i][j] = 0;
            }
            else
            {
                if(i < cost[j]) dp[i][j] = dp[i][j - 1];
                else dp[i][j] = dp[i - cost[j]][j - 1] + dp[i][j - 1];
            }
        }
    }
    std::cout << dp[m][n];

    return 0;
}

#endif

#if 0

#include<iostream>
#include<array>

constexpr int size = 10000 + 10;
constexpr int cost_size = 100 + 10;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    std::array<int,size> dp{};
    std::array<int,cost_size> cost{};
    for(int i = 1; i <= n;++i)
    {
        std::cin >> cost[i];
    }
    for(int i = 1; i <= n;++i)  //买物品
    {
        dp[0] = 1;
        for(int j = m;j >= cost[i];--j)  //钱
        {
            dp[j] += dp[j - cost[i]];
        }
    }
    std::cout << dp[m];

    return 0;
}

#endif