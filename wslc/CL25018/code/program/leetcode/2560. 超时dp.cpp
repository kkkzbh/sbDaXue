

#include<bits/stdc++.h>

// dp[n][k] = std::min(dp[n - 1][k] or std::max(a[n],dp[n - 2][k - 1])))

constexpr static int N{ 100000 + 2 };

std::array<std::array<int,N>,2> dp;

class Solution {
public:
    int minCapability(std::vector<int>& a, int k)
    {
        std::ranges::fill_n(dp[0].begin() + 1,k,std::numeric_limits<int>::max());
        std::ranges::fill_n(dp[1].begin() + 2,k - 1,std::numeric_limits<int>::max());
        dp[1][1] = a[0];
        for(int i : std::views::iota(2,static_cast<int>(a.size()) + 1))
        {
            for(int j : std::views::iota(1,std::min(k,i) + 1) | std::views::reverse)
            {
                dp[i % 2][j] = std::min(dp[(i + 1) % 2][j],std::max(a[i - 1],dp[i % 2][j - 1]));
            }
        }
        return dp[a.size() % 2][k];
    }
};