
#include<bits/stdc++.h>

struct Solution
{

    bool is(const char a,const char b)
    {
        if(b == 'a') return a == 'z';
        return b == a + 1;
    }

    int cv(const char c)
    {
        return c ^ 96;
    }

    int findSubstringInWraproundString(std::string& s)
    {
        int n = s.size();
        std::vector<int> a(n + 2,0);
        for(int i{}; i != n; ++i)
        {
            if(i and is(s[i - 1],s[i]))
            {
                a[i] = a[i - 1] + 1;
            }
        }
        int ret{};
        std::array<int,27> dp{};
        std::ranges::fill(dp,-1);
        for(int i{}; i != n; ++i)
        {
            int pos{ cv(s[i]) };
            dp[pos] = std::max(a[i],dp[pos]);
        }
        for(int i{ 1 }; i <= 26; ++i)
        {
            ret += dp[i] + 1;
        }

        return ret;
    }
};