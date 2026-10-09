

#include<bits/stdc++.h>

constexpr static int N{ 100 + 2 };

std::array<bool,N> dp;

class Solution {
public:
    bool isInterleave(std::string& s1, std::string& s2, std::string& s3)
    {
        memset(&dp,0,sizeof(dp));
        if(s1.size() + s2.size() != s3.size())
        {
            return false;
        }
        dp[0] = true;
        for(int j{ 1 }; j <= s2.size(); ++j)
        {
            dp[j] = s2[j - 1] == s3[j - 1] and dp[j - 1];
        }
        for(int i{ 1 }; i <= s1.size(); ++i)
        {
            for(int j{}; j <= s2.size(); ++j)
            {
                dp[j] = (i and s1[i - 1] == s3[i + j - 1] and dp[j])
                        or
                        (j and s2[j - 1] == s3[i + j - 1] and dp[j - 1]);
            }
        }
        return dp[s2.size()];
    }
};