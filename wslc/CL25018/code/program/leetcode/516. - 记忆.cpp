

#include<bits/stdc++.h>

constexpr static int N{ 1000 + 2 };

std::array<std::array<int,N>,N> dp;

class Solution{
public:

    int dfs(int l,int r,std::string& s)
    {
        if(l >= r)
        {
            return 0;
        }
        if(dp[l][r] != -1)
        {
            return dp[l][r];
        }
        if(r - l == 1)
        {
            return 1;
        }
        if(s[l] == s[r - 1])
        {
            return dp[l][r] = dfs(l + 1,r - 1,s) + 2;
        }
        return dp[l][r] = std::max(dfs(l,r - 1,s),dfs(l + 1,r,s));
    }

    int longestPalindromeSubseq(std::string& s)
    {
        memset(&dp,0xff,sizeof(dp));
        return dfs(0,s.size(),s);
    }
};