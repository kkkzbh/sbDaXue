

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>


#define fun auto
#define print(...) std::cout << std::format(__VA_ARGS__)

constexpr static int N{ 100 + 2 };
constexpr static int MOD{ 1000000 + 7 };

std::array<int,N> a,dp,prefix;
int n,m;

fun scan()
{
    std::cin >> n >> m;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin() + 1);
}

fun fdp()
{
    dp[0]= 1;
    for(int i{ 1 }; i <= n; ++i)
    {
        prefix[0] = 1;
        for(int j{ 1 }; j <= m; ++j)
        {
            prefix[j] = (prefix[j - 1] + dp[j]) % MOD;
        }
        for(int j{ m }; j >= 1; --j)
        {
            int pos{ j - std::min(j,a[i]) - 1 };
            if(pos == -1)
            {
                pos = m + 1;
            }
            dp[j] = (dp[j] + prefix[j - 1] - prefix[pos] + MOD) % MOD;
        }
    }
}

fun put()
{
    print("{}",dp[m]);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    fdp();
    put();

    return 0;
}