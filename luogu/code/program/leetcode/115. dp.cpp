
#include<bits/stdc++.h>

constexpr static int MOD{ 1000000000 + 7 };
constexpr static int N{ 1000 + 2 };

std::array<std::array<int,N>,N> dp;

class Solution {
public:

    int numDistinct(std::string& s, std::string& t)
    {
        memset(&dp,0,sizeof(dp));
        for(int i = s.size(); i >= 0; --i)
        {
            for(int j = t.size(); j >= 0; --j)
            {
                if(j == t.size())
                {
                    dp[i][j] = 1;
                }
                else if(i != s.size())
                {
                    if(s[i] == t[j])
                    {
                        dp[i][j] = (dp[i + 1][j + 1] + dp[i + 1][j]) % MOD;
                    }
                    else
                    {
                        dp[i][j] = dp[i + 1][j];
                    }
                }
            }
        }
        return dp[0][0];
    }
};