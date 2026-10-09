

#include<bits/stdc++.h>

class Solution {
public:

    int solve(int bound,std::vector<int>& a,int k)
    {
        int ret{};
        for(int i{}; i < a.size(); ++i)
        {
            if(a[i] <= bound)
            {
                ++ret;
                ++i;
            }
        }
        return ret;
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
