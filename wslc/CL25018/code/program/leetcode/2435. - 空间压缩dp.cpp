

#include<bits/stdc++.h>

constexpr static int MOD{ 1000000000 + 7 };

class Solution {
public:

#define m a.size()
#define n a[0].size()

    int numberOfPaths(std::vector<std::vector<int>>& a, int k)
    {
        std::vector<std::vector<int>> dp{ n + 1,std::vector<int>(k + 1,0) } ;
        dp[n - 1][a[m - 1][n - 1] % k] = 1;
        for(int j = n - 2; j >= 0; --j)
        {
            for(int r{}; r != k; ++r)
            {
                dp[j][r] = dp[j + 1][(r - (a[m - 1][j] % k) + k) % k];
            }
        }
        for(int i = m - 2 ; i >= 0; --i)
        {
            for(int j = n - 1; j >= 0; --j)
            {
                auto arr{ dp[j] };
                std::ranges::fill(dp[j],0);
                for(int r{}; r != k; ++r)
                {
                    int nr{ (r - (a[i][j] % k) + k) % k };
                    dp[j][r] = (arr[nr] + dp[j + 1][nr]) % MOD;
                }
            }
        }
        return dp[0][0];
    }
};
