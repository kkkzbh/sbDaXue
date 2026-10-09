

#include<bits/stdc++.h>

struct Solution
{

#define check(x,y) (x >= 0 and x < a.size() and y >= 0 and y < a[0].size())

    constexpr static int N{ 6 + 2 };
    constexpr static std::array move{ -1,0,1,0,-1 };

    std::array<std::bitset<N>,N> vis;

    bool dfs(int x,int y,int dep,auto& a,std::string& s)
    {
        if(dep + 1 == s.size())
        {
            return true;
        }
        vis[x][y] = true;
        bool tag{};
        for(int i{}; i != 4; ++i)
        {
            int mx{ x + move[i] };
            int my{ y + move[i + 1] };
            if(check(mx,my) and !vis[mx][my] and a[mx][my] == s[dep + 1])
            {
                if(dfs(mx,my,dep + 1,a,s))
                {
                    tag = true;
                    break;
                }
            }
        }
        vis[x][y] = false;
        return tag;
    }

    bool exist(std::vector<std::vector<char>>& a, std::string& s)
    {
        for(int i{}; i != a.size(); ++i)
        {
            for(int j{}; j != a[0].size(); ++j)
            {
                if(a[i][j] == s[0] and dfs(i,j,0,a,s))
                {
                    return true;
                }
            }
        }
        return false;
    }
};