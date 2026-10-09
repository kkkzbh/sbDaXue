

#include"bits/stdc++.h"
using namespace std;

// dp[i][k] = max -> dp[i - 1][k] | dp[i - 1][k - 1] + v1 | dp[i - 1][k - 2] + v1 + v2 ...

class Solution {
public:
    int maxValueOfCoins(vector<vector<int>>& a, int k)
    {
        std::vector<int> dp(k + 1);
        for (int i : std::views::iota(0, static_cast<int>(a.size()))) // enumerate the first i heaps
        {
            for (int j : std::views::iota(1, k + 1) | std::views::reverse) //
            {
                int sum{};
                for (int v : std::views::iota(1, std::min(j, static_cast<int>(a[i].size())) + 1))
                {
                    sum += a[i][v - 1];
                    dp[j] = std::max(dp[j], sum + dp[j - v]);
                }
            }
        }
        return dp[k];
    }
};
