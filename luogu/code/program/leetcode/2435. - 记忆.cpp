

#include<bits/stdc++.h>

constexpr static int MOD{ 1000000000 + 7 };

class Solution {
public:

#define m a.size()
#define n a[0].size()

    int dfs(int i,int j,int r,auto& a,int k,auto& dp)
    {
        if(i == m - 1 and j == n - 1)
        {
            return (a[i][j] % k) == r;
        }
        if(i >= m or j >= n)
        {
            return 0;
        }
        if(dp[i][j][r] != -1)
        {
            return dp[i][j][r];
        }
        int nr{ (r - (a[i][j] % k) + k) % k };
        return dp[i][j][r] = (dfs(i + 1,j,nr,a,k,dp) +
                              dfs(i,j + 1,nr,a,k,dp)) % MOD;
    }

    int numberOfPaths(std::vector<std::vector<int>>& a, int k)
    {
        std::vector<std::vector<std::vector<int>>> dp{ m,std::vector<std::vector<int>>{ n,std::vector<int>(k + 1,-1) } };
        return dfs(0,0,0,a,k,dp);
    }
};
