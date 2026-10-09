

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int kIncreasing(vector<int>& a, int k)
    {
        int ret{};
        for(int i : std::views::iota(0,k))
        {
            std::vector<int> ends;
            int sz{};
            for(int j{ i }; j < a.size(); j += k)
            {
                ++sz;
                auto it{ std::ranges::upper_bound(ends,a[j]) };
                if(it == ends.end())
                {
                    ends.push_back(a[j]);
                }
                else
                {
                    *it = std::min(*it,a[j]);
                }
            }
            ret += sz - ends.size();
        }
        return ret;
    }
};