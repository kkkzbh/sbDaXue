

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findNumberOfLIS(vector<int>& a)
    {
        std::vector<std::vector<int>> dp{ 1 },cnt{ 1 };
        dp[0].push_back(std::numeric_limits<int>::min()); // sentry
        cnt[0].push_back(1);
        for(int val : a)
        {
            auto it{ std::ranges::lower_bound(dp | std::views::drop(1),val,std::less<>{},[](auto& v){ return v.back(); }) };
            int index{ static_cast<int>(it - dp.begin()) };
            int i{ static_cast<int>(std::distance(dp[index - 1].begin(),std::ranges::upper_bound(dp[index - 1],val,std::greater<>{}))) };
            if(it == dp.end())
            {
                dp.emplace_back(1,val);
                cnt.emplace_back(1,cnt[index - 1].back() - (i ? cnt[index - 1][i - 1] : 0));
            }
            else
            {
                it->push_back(val);
                cnt[index].push_back(cnt[index - 1].back() - (i ? cnt[index - 1][i - 1] : 0) + cnt[index].back());
            }
        }
        return cnt.back().back();
    }
};
