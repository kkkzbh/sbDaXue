

#include<bits/stdc++.h>

constexpr static int N{ 30 + 2 };

std::array<std::array<std::array<bool,N>,N>,N> dp;

class Solution {
public:

    bool isScramble(std::string& s1, std::string& s2)
    {
        memset(&dp,0,sizeof(dp));
        for(int s = s2.size() - 1; s >= 0; --s)
        {
            for(int l = s1.size() - 1; l >= 0; --l)
            {
                for(int r{ l + 1 },cei = std::min(l + s2.size() - s,s1.size()); r <= cei; ++r)
                {
                    if(r - l == 1)
                    {
                        dp[l][r][s] = s1[l] == s2[s];
                    }
                    else
                    {
                        for (int cut{ l + 1 }; cut != r; ++cut)
                        {
                            if(dp[l][cut][s] and dp[cut][r][s + cut - l]
                                                                or
                                                                dp[l][cut][s + r - cut] and dp[cut][r][s])
                            {
                                dp[l][r][s] = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
        return dp[0][s1.size()][0];
    }
};