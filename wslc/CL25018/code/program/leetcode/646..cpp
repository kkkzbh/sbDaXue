

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findLongestChain(vector<vector<int>>& a)
    {
        std::ranges::sort(a,[](const auto& v1,const auto& v2)
        {
            return v1[0] < v2[0];
        });
        std::vector<std::vector<int>> ends;
        for(int i : std::views::iota(0,static_cast<int>(a.size())))
        {
            auto it{ std::ranges::lower_bound(ends,a[i],[](const auto& v1,const auto& v2)
            {
                return v1[1] < v2[0];
            }) };
            if(it == std::ranges::end(ends))
            {
                ends.push_back(a[i]);
            }
            else
            {
                it->back() = std::min(it->back(),a[i][1]);
            }
        }
        return ends.size();
    }
};