

#include<bits/stdc++.h>

#define fun auto

struct Solution
{

    using int64 = long long;

    constexpr static int mod{ 1000000000 + 7 };

    fun cv(int c) -> int
    {
        return c - 97;
    }

    fun distinctSubseqII(std::string& s) -> int
    {
        std::array<int,26> a{};
        int ret{ 1 };
        for(const char c : s)
        {
            int ad{ (ret - a[cv(c)] + mod) % mod };
            a[cv(c)] = static_cast<int>((a[cv(c)] + static_cast<int64>(ad)) % mod);
            ret = static_cast<int>((static_cast<int64>(ret) + ad) % mod);
        }
        return (ret - 1 + mod) % mod;
    }
};