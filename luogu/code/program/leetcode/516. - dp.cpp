

#include<bits/stdc++.h>

constexpr static int N{ 1000 + 2 };

std::array<std::array<int,N>,N> dp;

class Solution{
public:

    int longestPalindromeSubseq(std::string& s)
    {
        memset(&dp,0,sizeof(dp));
        for(int i{ static_cast<int>(s.size()) }; i; --i)
        {
            for(int j{ i + 1 }; j <= s.size() + 1; ++j)
            {
                if(j - i == 1)
                {
                    dp[i][j] = 1;
                }
                else if(s[i - 1] == s[j - 2])
                {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                }
                else
                {
                    dp[i][j] = std::max(dp[i + 1][j],dp[i][j - 1]);
                }
            }
        }
        return dp[1][s.size() + 1];
    }
};