

#include<bits/stdc++.h>

class Solution {
public:

    int dfs(int i,int bound,std::vector<int>& a,auto& dp)
    {
        if(i <= 0)
        {
            return 0;
        }
        if(dp[i] != -1)
        {
            return dp[i];
        }
        return dp[i] = std::max(dfs(i - 1,bound,a,dp),
                                a[i - 1] <= bound ? dfs(i - 2,bound,a,dp) + 1 : 0);
    }

    int solve(int bound,std::vector<int>& a,int k)
    {
        std::vector<int> dp(a.size() + 1,-1);
        return dfs(a.size(),bound,a,dp);
    }

    int minCapability(std::vector<int>& a, int k)
    {
        int l{ 1 },r{ 1000000000 + 1 };
        while(l != r)
        {
            int mid{ (l + r) >> 1 };
            if(solve(mid,a,k) >= k)
            {
                r = mid;
            }
            else
            {
                l = mid + 1;
            }
        }
        return l;
    }
};
