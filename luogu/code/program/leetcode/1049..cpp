

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lastStoneWeightII(vector<int>& a)
    {
        int sum{ std::accumulate(a.begin(),a.end(),int{}) };
        int cap{ sum >> 1 };
        std::vector<int> dp(cap + 1);
        for(int val : a)
        {
            for(int k : std::views::iota(std::min(val,cap + 1),cap + 1) | std::views::reverse)
            {
                dp[k] = std::max(dp[k],val + dp[k - val]);
            }
        }
        return sum - (dp[cap] << 1);
    }
};