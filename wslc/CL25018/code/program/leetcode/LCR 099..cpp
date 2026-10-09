

#include<bits/stdc++.h>

struct Solution
{

#define check(x,y) (x >= 0 and x < a.size() and y >= 0 and y <= a[0].size())

    constexpr static int INF{ 2147483647 >> 1 };

    int minPathSum(std::vector<std::vector<int>>& a)
    {
        for(int i{}; i != a.size(); ++i)
        {
            for(int j{}; j != a[0].size(); ++j)
            {
                if(i or j) [[likely]]
                {
                    a[i][j] += std::min(check(i,j - 1) ? a[i][j - 1] : INF,check(i - 1,j) ? a[i - 1][j] : INF);
                }
            }
        }
        return a[a.size() - 1][a[0].size() - 1];
    }
};