

#include<bits/stdc++.h>
using namespace std;

// S(A) - S(B) == target
// S(A) - S(B) + S(A) + S(B) == target + S(A) + S(B)
// 2 * S(A) == target + sum
// S(A) == (target + sum) >> 1 = new(target)
// Then we can know new(target) is greater than zero and must an even number.

// dp[n][k] = dp[n - 1][k] + dp[n - 1][k - vi]

class Solution {
public:
    int findTargetSumWays(vector<int>& a, int target)
    {
        int sum{ std::accumulate(a.begin(),a.end(),int{}) };
        if(sum < std::abs(target) or (sum & 1) ^ (target & 1))
        {
            return 0;
        }
        target = (target + sum) >> 1;
        std::vector<int> dp(sum + 1);
        dp[a[0]] = 1;
        dp[0] += 1;
        for(int i : std::views::iota(1,static_cast<int>(a.size()))) // can optimise the index using val
        {
            for(int k : std::views::iota(a[i],sum + 1) | std::views::reverse)
            {
                dp[k] += dp[k - a[i]];
            }
        }
        return dp[target];
    }
};