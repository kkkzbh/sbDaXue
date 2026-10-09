

#include<bits/stdc++.h>

constexpr static int N{ 30 + 2 };

std::array<std::array<std::array<char,N>,N>,N> dp;

class Solution {
public:

    bool dfs(int l,int r,int s,std::string& s1,std::string& s2)
    {
        if(r - l == 1)
        {
            return dp[l][r][s] = s1[l] == s2[s];
        }
        if(dp[l][r][s] != -1)
        {
            return dp[l][r][s];
        }
        for(int cut{ l + 1 }; cut != r; ++cut)
        {
            if(dfs(l,cut,s,s1,s2) and dfs(cut,r,s + cut - l,s1,s2)
                                      or
                                      dfs(l,cut,s + r - cut,s1,s2) and dfs(cut,r,s,s1,s2))
            {
                return dp[l][r][s] = true;
            }
        }
        return dp[l][r][s] = false;
    }

    bool isScramble(std::string& s1, std::string& s2)
    {
        memset(&dp,0xff,sizeof(dp));
        return dfs(0,s1.size(),0,s1,s2);
    }
};