

#include<bits/stdc++.h>

class Solution {
public:

    bool dfs(int i,int cnt,int bound,std::vector<int>& a,auto& dp)
    {
        if(!cnt)
        {
            return true;
        }
        if(i < cnt)
        {
            return false;
        }
        if(dp[i][cnt] != -1)
        {
            return dp[i][cnt];
        }
        bool ret{ dfs(i - 1,cnt,bound,a,dp) };
        if(a[i - 1] <= bound)
        {
            ret = std::max(ret,dfs(i - 2,cnt - 1,bound,a,dp));
        }
        return dp[i][cnt] = ret;
    }

    bool solve(int bound,std::vector<int>& a,int k)
    {
        std::vector<std::vector<char>> dp{
                a.size() + 1,std::vector<char>(k + 1,-1)
        };
        return dfs(a.size(),k,bound,a,dp);
    }

    int minCapability(std::vector<int>& a, int k)
    {
        int l{ 1 },r{ 1000000000 + 1 };
        while(l != r)
        {
            int mid{ (l + r) >> 1 };
            if(solve(mid,a,k))
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
