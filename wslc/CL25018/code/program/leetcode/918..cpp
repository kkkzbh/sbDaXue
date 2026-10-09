

#include<bits/stdc++.h>

class Solution {
public:
    int maxSubarraySumCircular(std::vector<int>& a)
    {
        int sum{ std::accumulate(a.begin(),a.end(),0) };
        int max{ a[0] },min{ max },dpmax{},dpmin{};
        for(int i : std::views::iota(0,static_cast<int>(a.size())))
        {
            max = std::max(max,dpmax = std::max(dpmax + a[i],a[i]));
            min = std::min(min,dpmin = std::min(dpmin + a[i],a[i]));
        }
        return min == sum ? max : std::max(max,sum - min);
    }
};