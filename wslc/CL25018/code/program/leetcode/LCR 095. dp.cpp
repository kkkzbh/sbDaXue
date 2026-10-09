

#include<bits/stdc++.h>

constexpr static int N{ 1000 + 2 };

std::array<int,N> dp;

struct Solution
{

    int longestCommonSubsequence(std::string& s1, std::string& s2)
    {
        memset(&dp,0,sizeof(dp));
        for(int i{ 1 }; i <= s1.size(); ++i)
        {
            int leftup{};
            for(int j{ 1 }; j <= s2.size(); ++j)
            {
                int tmp{ dp[j] };
                if(s1[i - 1] == s2[j - 1])
                {
                    dp[j] = leftup + 1;
                }
                else
                {
                    dp[j] = std::max(dp[j],dp[j - 1]);
                }
                leftup = tmp;
            }
        }
        return dp[s2.size()];
    }

};