

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& a)
    {
        std::vector<int> ends;
        ends.reserve(a.size());
        for(int i : std::views::iota(0,static_cast<int>(a.size())))
        {
            auto it{ std::ranges::lower_bound(ends,a[i]) };
            if(it == ends.end())
            {
                ends.push_back(a[i]);
            }
            else if(a[i] < *it)
            {
                *it = a[i];
            }
        }
        return ends.size();
    }
};