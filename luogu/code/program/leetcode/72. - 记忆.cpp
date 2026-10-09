

#include<bits/stdc++.h>

constexpr static int N{ 500 + 2 };

std::array<std::array<int,N>,N> dp;

class Solution {
public:

    constexpr static int INF{ 2147483647 >> 1 };

    int dfs(int len1,int len2,const std::string& s1,const std::string& s2)
    {
        if(!len2)
        {
            return len1;
        }
        if(!len1)
        {
            return len2;
        }
        if(dp[len1][len2] != -1)
        {
            return dp[len1][len2];
        }
        if(s1[len1 - 1] == s2[len2 - 1])
        {
            return dp[len1][len2] = dfs(len1 - 1,len2 - 1,s1,s2);
        }
        return dp[len1][len2] = 1 + std::min({
                                                     dfs(len1,len2 - 1,s1,s2),
                                                     dfs(len1 - 1,len2,s1,s2),
                                                     dfs(len1 - 1,len2 - 1,s1,s2)
                                             });
    }

    int minDistance(std::string& s1, std::string& s2)
    {
        memset(&dp,0xff,sizeof(dp));
        return dfs(s1.size(),s2.size(),s1,s2);
    }
};