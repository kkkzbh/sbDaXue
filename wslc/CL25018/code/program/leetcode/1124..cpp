

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

#define n int(a.size())

    int longestWPI(vector<int>& a)
    {
        std::unordered_map<int,int> map;
        int sum{},ret{};
        for(int i : std::views::iota(0,static_cast<int>(a.size())))
        {
            sum += a[i] > 8 ? 1 : -1;
            if(sum > 0)
            {
                ret = i + 1;
            }
            else if(map.contains(sum - 1))
            {
                ret = std::max(ret,i - map[sum - 1]);
            }
            if(!map.contains(sum))
            {
                map.emplace(sum,i);
            }
        }
        return ret;
    }
};