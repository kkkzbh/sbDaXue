

#include<bits/stdc++.h>

constexpr static int N{ 100 + 2 };

std::array<int,N> dp;

class Solution {
public:
    int rob(std::vector<int>& a)
    {
        memset(&dp,0,sizeof(dp));
        dp[0] = 0;
        dp[1] = a[0];
        for(int i : std::views::iota(2,static_cast<int>(a.size()) + 1))
        {
            dp[i] = std::max(dp[i - 1],a[i - 1] + dp[i - 2]);
        }
        return dp[a.size()];
    }
};