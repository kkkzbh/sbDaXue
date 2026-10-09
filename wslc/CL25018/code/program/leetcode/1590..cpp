

#include<bits/stdc++.h>
using namespace std;

using int64 = long long;

class Solution {
public:

#define n static_cast<int>(a.size())

    int minSubarray(vector<int>& a, int p)
    {
        std::unordered_map<int,int> map{ { 0,-1 } };
        int64 sum{ std::accumulate(a.begin(),a.end(),int64{}) };
        int mod{ static_cast<int>(sum % p) };
        int ret{ std::numeric_limits<int>::max() };
        sum = 0;
        for(int i : std::views::iota(0,n))
        {
            sum += a[i];
            map[static_cast<int>(sum % p)] = i;
            if(int it{ static_cast<int>(((sum % p) - mod + p) % p) }; map.contains(it))
            {
                ret = std::min(ret, i - map[it]);
            }
        }
        return ret == n ? -1 : ret;
    }
};