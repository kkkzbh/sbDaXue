

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>
#include<cmath>
#include<numeric>
#include<cstring>
#include<functional>
#include<string>

#define fun auto
template<typename... Args>
fun print(const std::format_string<Args...> fmts,Args&&... args)
{
    if constexpr(sizeof...(Args))
    {
        std::cout << std::vformat(fmts.get(), std::make_format_args(std::forward<Args>(args)...));
    }
    else
    {
        std::cout << fmts.get();
    }
}

constexpr static int N{ 1000 + 2 };
constexpr static int N2{ 40000 + 2 };
constexpr static int MOD{ 998244353 };

int n;
std::array<int,N> a;
std::array<std::array<int,N2>,N> dp;   // dp[i][d] 表示前i个的方案数 公差为d的方案个数
std::array<int,N> cnt;

fun solve()
{
    std::cin >> n;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin() + 1);
    int del{ std::ranges::max(std::views::counted(a.begin() + 1,n)) - std::ranges::min(std::views::counted(a.begin() + 1,n)) };
    // 一个序列为等差数列 求其方案数
    // dp[i][d] = sum if a[i] = a[k] + d -> dp[0,1,2,3...i - 1][d]


    std::ranges::for_each(dp,[](auto& v){ v.fill(1); });
    std::ranges::fill(std::views::counted(cnt.begin() + 1,n),1);

    for(int i : std::views::iota(1,n + 1))
    {
        for(int j: std::views::iota(1, i))
        {
            dp[i][del + a[i] - a[j]] = (dp[i][del + a[i] - a[j]] + dp[j][del + a[i] - a[j]]) % MOD;
            cnt[i] = (cnt[i] + dp[j][del + a[i] - a[j]]) % MOD;
        }
    }

    print("{}",std::accumulate(cnt.begin() + 1,cnt.begin() + n + 1,int{},[](int x,int v){ return (x + v) % MOD; }));
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}