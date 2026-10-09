

#include<bits/stdc++.h>
using namespace std;

// dp[i][k] = dp[i - 1][k - vi] + dp[i - 1][k + vi]

constexpr static int trans{ 1000 };
constexpr static int Ni{ 20 + 2 };
constexpr static int Nk{ (trans << 1) + 2 };

std::array<std::array<int,Nk>,Ni> dp;

class Solution {
public:
    int findTargetSumWays(vector<int>& a, int target)
    {
        memset(&dp,0,sizeof(dp));
        dp[1][trans + a[0]] += 1;
        dp[1][trans - a[0]] += 1;
        for(int i : std::views::iota(1,static_cast<int>(a.size())))
        {
            for(int k : std::views::iota(0,2000 + 1))
            {
                dp[i + 1][k] += k + a[i] <= 2000 ? dp[i][k + a[i]] : 0;
                dp[i + 1][k] += k - a[i] >= 0 ? dp[i][k - a[i]] : 0;
            }
        }
        return dp[a.size()][trans + target];
    }
};