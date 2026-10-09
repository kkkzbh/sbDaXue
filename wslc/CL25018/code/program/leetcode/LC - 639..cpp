

#include<bits/stdc++.h>

[[maybe_unused]] auto init = []{ std::ios::sync_with_stdio(0),std::cin.tie(0); return bool{}; }();

struct Solution
{
    constexpr static int N{ 100000 + 2 };
    constexpr static int MOD{ 1000000000 + 7 };
    using int64 = long long;

    std::array<int,N> a;

    int numDecodings(const std::string& s)
    {
        int n = s.size();
        a[n] = 1;
        for(int i{ n }; i--;)
        {
            if(s[i] != '*')
            {
                int val{ s[i] ^ 48 };
                if(val >= 1 and val <= 9)
                {
                    a[i] = (static_cast<int64>(a[i]) + a[i + 1]) % MOD;
                }
                if(i + 1 != n)
                {
                    if(s[i + 1] != '*')
                    {
                        val *= 10;
                        val += s[i + 1] ^ 48;
                        if(val >= 10 and val <= 26)
                        {
                            a[i] = (static_cast<int64>(a[i]) + a[i + 2]) % MOD;
                        }
                    }
                    else
                    {
                        if(val == 1)
                        {
                            a[i] = (a[i] + 9ll * a[i + 2]) % MOD;
                        }
                        else if(val == 2)
                        {
                            a[i] = (a[i] + 6ll * a[i + 2]) % MOD;
                        }
                    }
                }
            }
            else
            {
                a[i] = (a[i] + 9ll * a[i + 1]) % MOD;
                if(i + 1 != n)
                {
                    if(s[i + 1] != '*')
                    {
                        int v{ s[i + 1] ^ 48 };
                        if(v <= 6)
                        {
                            a[i] = (a[i] + 2ll * a[i + 2]) % MOD;
                        }
                        else
                        {
                            a[i] = (static_cast<int64>(a[i]) + a[i + 2]) % MOD;
                        }
                    }
                    else
                    {
                        a[i] = (a[i] + 15ll * a[i + 2]) % MOD;  // 9 + 6
                    }
                }
            }
        }
        return a[0];
    }
};