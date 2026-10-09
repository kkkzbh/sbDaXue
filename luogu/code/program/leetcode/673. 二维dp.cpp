

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findNumberOfLIS(vector<int>& a)
    {
        std::vector<int> len(a.size(),1);
        std::vector<int> cnt(a.size(),1);
        for(int i : std::views::iota(0,static_cast<int>(a.size())))
        {
            int l{},c{};
            for(int j : std::views::iota(0,i) | std::views::filter([&a,i](int j){ return a[j] < a[i]; }))
            {
                if(len[j] > l)
                {
                    l = len[j];
                    c = cnt[j];
                }
                else if(len[j] == l)
                {
                    c += cnt[j];
                }
            }
            if(l + 1 > len[i])
            {
                len[i] = l + 1;
                cnt[i] = c;
            }
            else if(l + 1 == len[i])
            {
                cnt[i] += c;
            }
        }
        int l{},c{};
        for(int i : std::views::iota(0,static_cast<int>(a.size())))
        {
            if(len[i] > l)
            {
                l = len[i];
                c = cnt[i];
            }
            else if(l == len[i])
            {
                c += cnt[i];
            }
        }
        return c;
    }
};