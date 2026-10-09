
#include<bits/stdc++.h>

constexpr static int MOD{ 1000000000 + 7 };
constexpr static int N{ 1000 + 2 };

std::array<int,N> dp;

class Solution {
public:

    int numDistinct(std::string& s, std::string& t)
    {
        memset(&dp,0,sizeof(dp));
        dp[t.size()] = 1;
        for(int i = s.size() - 1; i >= 0; --i)
        {
            for(int j{}; j != t.size(); ++j)
            {
                if(s[i] == t[j])
                {
                    dp[j] = (dp[j + 1] + dp[j]) % MOD;
                }
            }
        }
        return dp[0];
    }
};