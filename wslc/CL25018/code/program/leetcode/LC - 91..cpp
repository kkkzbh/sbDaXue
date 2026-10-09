
#include<bits/stdc++.h>

[[maybe_unused]]
auto init = []
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    return bool{};
}();

struct Solution
{

    constexpr static int N{ 100 + 2 };
    std::array<int,N> a{};

    int dfs(int i,const std::string& s)
    {
        if(i == s.size())
        {
            return 1;
        }
        if(a[i] != -1)
        {
            return a[i];
        }
        int val{ s[i] ^ 48 };
        int ret{};
        if(val >= 1 and val <= 9)
        {
            ret += dfs(i + 1,s);
        }
        if(i + 1 != s.size())
        {
            val *= 10;
            val += s[i + 1] ^ 48;
            if(val >= 10 and val <= 26)
            {
                ret += dfs(i + 2, s);
            }
        }
        return a[i] = ret;
    }

    int numDecodings(const std::string& s)
    {
        std::fill(a.begin(),a.begin() + s.size(),-1);
        return dfs(0,s);
    }
};