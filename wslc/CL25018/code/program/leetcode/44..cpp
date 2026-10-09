

#include<bits/stdc++.h>
using namespace std;


//dp[i][j] =
// c? -> (s[i - 1] == p[j - 1] or p[j - 1] == '?') and dp[i - 1][j - 1]
// * -> dp[i][j - 1] or dp[i - 1][j]

constexpr static int N{ 2000 + 2 };

std::array<std::bitset<N>,N> dp;

class Solution {
public:
    bool isMatch(string& s, string& p)
    {
        memset(&dp,0,sizeof(dp));
        dp[0][0] = true;
        for(int j : std::views::iota(1,static_cast<int>(p.size()) + 1))
        {
            if(!(dp[0][j] = p[j - 1] == '*'))
            {
                break;
            }
        }
        for(int i : std::views::iota(1,static_cast<int>(s.size()) + 1))
        {
            for(int j : std::views::iota(1,static_cast<int>(p.size()) + 1))
            {
                if(p[j - 1] == '*')
                {
                    dp[i][j] = dp[i][j - 1] or dp[i - 1][j];
                }
                else
                {
                    dp[i][j] = (s[i - 1] == p[j - 1] or p[j - 1] == '?') and dp[i - 1][j - 1];
                }
            }
        }
        return dp[s.size()][p.size()];
    }
};