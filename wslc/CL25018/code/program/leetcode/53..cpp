

#include<bits/stdc++.h>

constexpr static int N{ 100000 + 2 };

std::array<int,N> dp;

class Solution {
public:
    int maxSubArray(std::vector<int>& a)
    {
        memset(&dp,0,sizeof(dp));
        int ret{ a[0] };
        for(int i : std::views::iota(1,static_cast<int>(a.size()) + 1))
        {
            ret = std::max(dp[i] = std::max(a[i - 1],a[i - 1] + dp[i - 1]),ret);
        }
        return ret;
    }
};