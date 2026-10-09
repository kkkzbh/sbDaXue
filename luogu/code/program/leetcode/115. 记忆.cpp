
#include<bits/stdc++.h>

constexpr static int MOD{ 1000000000 + 7 };
constexpr static int N{ 1000 + 2 };

std::array<std::array<int,N>,N> dp;

class Solution {
public:

    int dfs(int i,int k,const std::string& s,const std::string& t)
    {
        if(dp[i][k] != -1)
        {
            return dp[i][k];
        }
        if(k == t.size())
        {
            return 1;
        }
        if(i == s.size())
        {
            return 0;
        }
        if(s[i] == t[k])
        {
            return dp[i][k] = (dfs(i + 1,k + 1,s,t) + dfs(i + 1,k,s,t)) % MOD;
        }
        return dp[i][k] = dfs(i + 1,k,s,t) % MOD;
    }

    int numDistinct(std::string& s, std::string& t)
    {
        memset(&dp,0xff,sizeof(dp));
        return dfs(0,0,s,t);
    }
};