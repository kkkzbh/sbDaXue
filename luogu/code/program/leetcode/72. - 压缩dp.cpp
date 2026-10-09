

#include<bits/stdc++.h>

constexpr static int N{ 500 + 2 };

std::array<int,N> dp;

class Solution {
public:

    int minDistance(std::string& s1, std::string& s2)
    {
        memset(&dp,0xff,sizeof(dp));
        for(int j{}; j <= s2.size(); ++j)
        {
            dp[j] = j;
        }
        for(int i{ 1 }; i <= s1.size(); ++i)
        {
            int leftup{ dp[0] };
            dp[0] = i;
            for(int j{ 1 }; j <= s2.size(); ++j)
            {
                int tmp{ dp[j] };
                if(s1[i - 1] != s2[j - 1])
                {
                    dp[j] = 1 + std::min({ dp[j],dp[j - 1],leftup });
                }
                else
                {
                    dp[j] = leftup;
                }
                leftup = tmp;
            }
        }
        return dp[s2.size()];
    }
};