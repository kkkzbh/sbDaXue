

#include<bits/stdc++.h>
#include<ranges>

constexpr static int N{ 100 + 2 };
constexpr static int MOD{ 1000000000 + 7 };

std::array<std::array<int,N>,N> dp;

auto init = []
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    return char{};
}();

class Solution {
public:
    int profitableSchemes(int n, int minProfit, std::vector<int>& group, std::vector<int>& profit)
    {
        memset(&dp,0,sizeof(dp));
        for(int i{}; i <= n; ++i)
        {
            dp[i][0] = 1;
        }
        for(int k{}; k != profit.size(); ++k)
        {
            for(int i{ n }; i >= group[k]; --i)
            {
                for(int j{ minProfit }; j >= 0; --j)
                {
                    dp[i][j] = (dp[i][j] + dp[i - group[k]][std::max(0,j - profit[k])]) % MOD;
                }
            }
        }
        return dp[n][minProfit];
    }
};