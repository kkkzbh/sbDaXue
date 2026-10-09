

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& a)
    {
        std::ranges::sort(a,[](const auto& v1,const auto& v2)
        {
            if(v1[0] == v2[0])
            {
                return v1[1] > v2[1];
            }
            return v1[0] < v2[0];
        });
        std::vector<int> ends;
        for(int i : std::views::iota(0,static_cast<int>(a.size())))
        {
            auto it{ std::ranges::lower_bound(ends,a[i][1]) };
            if(it == ends.end())
            {
                ends.push_back(a[i][1]);
            }
            else
            {
                *it = std::min(*it,a[i][1]);
            }
        }
        return ends.size();
    }
};