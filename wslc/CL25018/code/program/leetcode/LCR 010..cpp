

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& a, int k)
    {
        int dp{},ret{};
        std::unordered_map<int,int> map;
        ++map[0];
        for(int i : std::views::iota(0,int(a.size())))
        {
            dp += a[i];
            ret += map[dp - k];
            ++map[dp];
        }
        return ret;
    }
};