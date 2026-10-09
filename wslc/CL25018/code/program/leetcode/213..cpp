

#include<bits/stdc++.h>

constexpr static int N{ 100 + 2 };

// dp[n] = std::max(a[n] + dp[n - 2],dp[n - 1])

class Solution {
public:
    int rob(std::vector<int>& a)
    {
        if(a.size() == 1)
        {
            return a[0];
        }
        std::array<int,2> dp{};
        int ret{};
        for(int i : std::views::iota(1,static_cast<int>(a.size())))
        {
            ret = std::max(a[i] + dp[0],dp[1]);
            dp[0] = dp[1];
            dp[1] = ret;
        }
        int ret2{};
        dp.fill(0);
        for(int i : std::views::iota(0,static_cast<int>(a.size() - 1)))
        {
            ret2 = std::max(a[i] + dp[0],dp[1]);
            dp[0] = dp[1];
            dp[1] = ret2;
        }
        std::cout << ret << ' ' << ret2;
        return std::max(ret,ret2);
    }
};