

#include<bits/stdc++.h>

constexpr static int N{ 200 + 2 };

std::array<std::bitset<N>,N> vis;

class Solution {
public:

    constexpr static std::array move{ -1,0,1,0,-1 };

    int m,n;

    bool check(int x,int y)
    {
        return x >= 0 and x < m and y >= 0 and y < n;
    }

    int dfs(int x,int y,auto& a)
    {
        vis[x][y] = true;
        int ret{ 1 };
        for(int i{}; i < 4; ++i)
        {
            int mx{ x + move[i] };
            int my{ y + move[i + 1] };
            if(check(mx,my)  and !vis[mx][my] and a[mx][my] > a[x][y])
            {
                ret = std::max(ret,dfs(mx,my,a) + 1);
            }
        }
        vis[x][y] = false;
        return ret;
    }

    int longestIncreasingPath(std::vector<std::vector<int>>& a)
    {
        m = int(a.size());
        n = int(a[0].size());
        int ret{};
        for(int i{}; i != m; ++i)
        {
            for(int j{}; j != n; ++j)
            {
                ret = std::max(ret,dfs(i,j,a));
            }
        }
        return ret;
    }
};