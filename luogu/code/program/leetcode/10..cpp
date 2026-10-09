

#include<bits/stdc++.h>
using namespace std;

// dp[i][j] =
// if c     s[i - 1] == p[j - 1] and dp[i - 1][j - 1]
// if *     不匹配 -> dp[i][j - 2]
//          匹配 -> (p[j - 2] == . or s[i - 1] == p[j - 2]) and dp[i - 1][j]
// if .     直接匹配 dp[i - 1][j - 1]

constexpr static int N{ 20 + 2 };

std::array<std::bitset<N>,N> dp;

class Solution {
public:
    bool isMatch(string& s, string& p)
    {
        memset(&dp,0,sizeof(dp));
        dp[0][0] = true;
        for(int j : std::views::iota(1,static_cast<int>(p.size()) + 1))
        {
            if(p[j - 1] == '*')
            {
                dp[0][j] = dp[0][j - 2];
            }
        }
        for(int i : std::views::iota(1,static_cast<int>(s.size()) + 1))
        {
            for(int j : std::views::iota(1,static_cast<int>(p.size()) + 1))
            {
                if(p[j - 1] == '.')
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else if(p[j - 1] == '*')
                {
                    dp[i][j] = dp[i][j - 2] or ((p[j - 2] == '.' or p[j - 2] == s[i - 1]) and dp[i - 1][j]);
                }
                else
                {
                    dp[i][j] = s[i - 1] == p[j - 1] and dp[i - 1][j - 1];
                }
            }
        }
        return dp[s.size()][p.size()];
    }
};
