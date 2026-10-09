

#include<bits/stdc++.h>

constexpr static int N{ 100 + 2 };
constexpr static int N2{ 200 + 2 };

std::array<std::array<bool,N>,N> dp;

class Solution {
public:
    bool isInterleave(std::string& s1, std::string& s2, std::string& s3)
    {
        memset(&dp,0,sizeof(dp));
        dp[0][0] = true;
        for(int k{ 1 }; k <= s3.size(); ++k)
        {
            for(int i = s1.size(); i >= 0; --i)
            {
                for(int j = s2.size(); j >= 0; --j)
                {
                    int tmp{};
                    dp[i][j] = false;
                    if(i and s1[i - 1] == s3[k - 1])
                    {
                        dp[i][j] |= dp[i - 1][j];
                        ++tmp;
                    }
                    if(j and s2[j - 1] == s3[k - 1])
                    {
                        dp[i][j] |= dp[i][j - 1];
                        ++tmp;
                    }
                    if(!tmp)
                    {
                        dp[i][j] = false;
                    }
                }
            }
        }
        return dp[s1.size()][s2.size()];
    }
};