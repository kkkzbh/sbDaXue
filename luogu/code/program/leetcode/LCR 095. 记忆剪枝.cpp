

#include<bits/stdc++.h>

constexpr static int N{ 1000 + 2 };

std::array<std::array<int,N>,N> dp;

struct Solution
{


    int dfs(int l1,int l2,std::string& s1,std::string& s2)
    {
        if(!l1 or !l2)
        {
            return 0;
        }
        if(dp[l1][l2] != -1)
        {
            return dp[l1][l2];
        }
        if(s1[l1 - 1] == s2[l2 - 1])
        {
            return dfs(l1 - 1,l2 - 1,s1,s2) + 1;
        }
        return dp[l1][l2] = std::max(dfs(l1 - 1,l2,s1,s2),dfs(l1,l2 - 1,s1,s2));
    }


    int longestCommonSubsequence(std::string& s1, std::string& s2)
    {
        memset(&dp,0xff,sizeof(dp));
        return dfs(s1.size(),s2.size(),s1,s2);
    }
};