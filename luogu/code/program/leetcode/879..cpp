

#include<bits/stdc++.h>
#include<ranges>

constexpr static int N{ 100 + 2 };
constexpr static int N2{ 10000 + 2 };
constexpr static int MOD{ 1000000000 + 7 };

std::array<std::array<int,N2>,N> dp;

class Solution {
public:
    int profitableSchemes(int n, int minProfit, std::vector<int>& group, std::vector<int>& profit)
    {
        int sum{ std::accumulate(profit.begin(),profit.end(),0) };
        if(sum < minProfit)
        {
            return 0;
        }
        memset(&dp,0,sizeof(dp));
        for(int i{}; i <= n; ++i)
        {
            dp[i][0] = 1;
        }
        for(int k{}; k != profit.size(); ++k)
        {
            for(int i{ n }; i >= group[k]; --i)
            {
                for(int j{ sum }; j >= profit[k];--j)
                {
                    dp[i][j] = (dp[i][j] + dp[i - group[k]][j - profit[k]]) % MOD;
                }
            }
        }

        return std::accumulate(dp[n].begin() + minProfit,dp[n].begin() + sum + 1,0,[](int x,int y)
        {
            return (x + y) % MOD;
        });
    }
};