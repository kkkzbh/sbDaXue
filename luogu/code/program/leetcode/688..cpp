

#include<bits/stdc++.h>

constexpr static int N{ 25 + 2 };
constexpr static int N2{ 100 + 2 };
constexpr static double eps{ 1e-6 };

std::array<std::array<std::array<double,N2>,N>,N> dp;

class Solution {
public:

    constexpr static std::array<std::array<int,2>,8> move
            {{
                     { -1,-2 },{ -2,-1 },{ -2,1 },{ -1,2 },
                     { 1,2 },{ 2,1 },{ 2,-1 },{ 1,-2 },
             }};

    double dfs(int x,int y,int k,int n)
    {
        if(x < 0 or x >= n or y < 0 or y >= n)
        {
            return 0.0;
        }
        if(!k)
        {
            return 1.0;
        }
        if(std::abs(dp[x][y][k] + 1) > eps)
        {
            return dp[x][y][k];
        }
        double ret{};
        for(const auto [dx,dy] : move)
        {
            int mx{ x + dx };
            int my{ y + dy };
            ret += dfs(mx,my,k - 1,n) / 8.0;
        }
        return dp[x][y][k] = ret;
    }

    double knightProbability(int n, int k, int row, int column)
    {
        for(auto& v1 : dp)
        {
            for(auto& v2 : v1)
            {
                v2.fill(-1.0);
            }
        }
        return dfs(row,column,k,n);
    }
};