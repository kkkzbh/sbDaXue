

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& a)
    {
        std::vector<int> dp(a.size(),1);
        for(int i : std::views::iota(1,static_cast<int>(a.size())))
        {
            for(int j : std::views::iota(0,i))
            {
                if(a[j] < a[i])
                {
                    dp[i] = std::max(dp[i],dp[j] + 1);
                }
            }
        }
        return std::ranges::max(dp);
    }
};