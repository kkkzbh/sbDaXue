

#include<bits/stdc++.h>

constexpr static int N{ 200 + 2 };

std::array<std::array<int,N>,N> prefix;
std::array<int,N> arr;

class Solution {
public:

#define n a.size()
#define m a[0].size()

    std::tuple<int,int,int> sum(int beg,int end,auto& a)
    {
        for(int i : std::views::iota(1,static_cast<int>(m) + 1))
        {
            arr[i] = prefix[end][i] - prefix[beg - 1][i];
        }
        int l,r,val{ std::numeric_limits<int>::min() },dp{},ll{ 1 };
        for(int i : std::views::iota(1,static_cast<int>(m) + 1))
        {
            if(dp > 0)
            {
                dp += arr[i];
            }
            else
            {
                dp = arr[i];
                ll = i;
            }
            if(dp > val)
            {
                l = ll;
                r = i;
                val = dp;
            }
        }
        return std::make_tuple(l,r,val);
    }

    std::vector<int> getMaxMatrix(std::vector<std::vector<int>>& a)
    {
        for(int i : std::views::iota(1,static_cast<int>(n) + 1))
        {
            for(int j : std::views::iota(1,static_cast<int>(m) + 1))
            {
                prefix[i][j] = prefix[i - 1][j] + a[i - 1][j - 1];
            }
        }

        int lx,ly,rx,ry,val{ std::numeric_limits<int>::min() };

        for(int i : std::views::iota(1,static_cast<int>(n) + 1))
        {
            for(int j : std::views::iota(i,static_cast<int>(n) + 1))
            {
                auto [ll,rr,vv]{ sum(i,j,a) };
                if(vv > val)
                {
                    lx = i;
                    ly = ll;
                    rx = j;
                    ry = rr;
                    val = vv;
                }
            }
        }
        return { lx - 1,ly - 1,rx - 1,ry - 1 };
    }
};