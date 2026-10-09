

#include<bits/stdc++.h>

constexpr static int N{ 200 + 2 };

std::array<std::array<int,N>,N> dp;

struct node
{
    int x,y;
};

class Solution {
public:

    constexpr static std::array move{ -1,0,1,0,-1 };

    int m,n;

    bool check(int x,int y)
    {
        return x >= 0 and x < m and y >= 0 and y < n;
    }

    int longestIncreasingPath(std::vector<std::vector<int>>& a)
    {
        m = int(a.size());
        n = int(a[0].size());
        auto cmp = [&a](const node n1,const node n2)
        {
            return a[n1.x][n1.y] > a[n2.x][n2.y];
        };
        std::priority_queue<node,std::vector<node>,decltype(cmp)> que{ cmp };
        for(int i{}; i != m; ++i)
        {
            for(int j{}; j != n; ++j)
            {
                que.emplace(i,j);
            }
        }

        for(auto& v : dp)
        {
            v.fill(1);
        }
        int ret{ 1 };
        while(!que.empty())
        {
            auto [x,y] = que.top();
            que.pop();
            for(int i{}; i < 4; ++i)
            {
                int mx{ x + move[i] };
                int my{ y + move[i + 1 ] };
                if(check(mx,my) and a[mx][my] > a[x][y])
                {
                    ret = std::max(ret,dp[mx][my] = std::max(dp[mx][my],1 + dp[x][y]));
                }
            }
        }
        return ret;
    }
};