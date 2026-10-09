

#include<bits/stdc++.h>

constexpr static int N{ 600 + 2 };
constexpr static int N2{ 100 + 2 };

std::array<std::pair<int,int>,N> a;
int sz;
std::array<std::array<int,N2>,N2> dp;

class Solution {
public:

    int findMaxForm(std::vector<std::string>& vec, int m, int n)
    {
        sz = vec.size();
        for(int i{ 1 }; i <= sz; ++i)
        {
            int f{},s{};
            for(const auto c : vec[i - 1])
            {
                if(c == '0')
                {
                    ++f;
                }
                else
                {
                    ++s;
                }
            }
            a[i] = std::make_pair(f,s);
        }

        memset(&dp,0,sizeof(dp));

        for(int k{ 1 }; k <= sz; ++k)
        {
            for(int i{ m }; i >= a[k].first; --i)
            {
                for(int j{ n }; j >= a[k].second; --j)
                {
                    dp[i][j] = std::max(dp[i][j],1 + dp[i - a[k].first][j - a[k].second]);
                }
            }
        }

        return dp[m][n];
    }



};