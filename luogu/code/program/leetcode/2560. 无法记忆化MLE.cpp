

#include<bits/stdc++.h>


// dp[n][k] = std::min(dp[n - 1][k] or std::max(a[n],dp[n - 2][k - 1])))
// dp[k] = std::min(dp[k],std::max(a[n],dp[k - 1]))

constexpr static int N{ 100000 + 2 };

std::array<std::array<int,((N + 1 ) >> 1)>,N> dp;

int dfs(int i,int j,std::vector<int>& a)
{
    if(i <= 0 or !j)
    {
        return 0;
    }
    if(((i + 1) >> 1) < j)
    {
        return std::numeric_limits<int>::max();
    }
    if(i == j == 1)
    {
        return a[0];
    }
    if(dp[i][j] != -1)
    {
        return dp[i][j];
    }
    return dp[i][j] =  std::min(dfs(i - 1,j,a),std::max(dfs(i - 2,j - 1,a),a[i - 1]));
}

class Solution {
public:
    int minCapability(std::vector<int>& a, int k)
    {
        memset(&dp,0xff,sizeof(dp));
        return dfs(a.size(),k,a);
    }
};