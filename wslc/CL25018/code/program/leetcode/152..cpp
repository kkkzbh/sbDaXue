

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    using int64 = long long;

#define n static_cast<int>(a.size())

    int maxProduct(vector<int>& a)
    {
        int ret{ a[0] },dp[2]{ a[0],a[0] };    // dp[0] 为 max dp[i - 1]   dp[1] = min dp[i - 1]
        for(int i : std::views::iota(1,n))
        {
            int max,min;
            int64 val = a[i];
            if(a[i] > 0)
            {
                max = std::max(val,val * dp[0]);
                min = std::min(val,val * dp[1]);
            }
            else
            {
                max = std::max(val,val * dp[1]);
                min = std::min(val,val * dp[0]);
            }
            dp[0] = max;
            dp[1] = min;
            ret = std::max(ret,max);
        }
        return ret;
    }
};
