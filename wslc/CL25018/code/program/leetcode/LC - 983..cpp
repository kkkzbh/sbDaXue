

#include<bits/stdc++.h>

auto init{ []
           {
               std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
               return char{};
           }()};

struct Solution
{

    constexpr static int N{ 365 + 2 };

    int ans{ std::numeric_limits<int>::max() };
    std::array<int,N> t;

    void dfs(int i,int m,std::vector<int>& a,std::vector<int>& c)
    {
        if(i == a.size())
        {
            ans = std::min(ans,m);
        }
        else
        {
            if(t[i] > m)
            {
                dfs(std::lower_bound(a.begin() + i, a.end(), a[i] + 1) - a.begin(), m + c[0], a, c);
                dfs(std::lower_bound(a.begin() + i, a.end(), a[i] + 7) - a.begin(), m + c[1], a, c);
                dfs(std::lower_bound(a.begin() + i, a.end(), a[i] + 30) - a.begin(), m + c[2], a, c);
                t[i] = m;
            }
        }
    }


    int mincostTickets(std::vector<int>& a, std::vector<int>& c)
    {
        t.fill(std::numeric_limits<int>::max());
        dfs(0,0,a,c);
        return ans;
    }
};