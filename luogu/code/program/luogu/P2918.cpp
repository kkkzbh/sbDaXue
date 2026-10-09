

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

constexpr static int N{ 100 + 2 };

struct node
{
    fun friend operator>>(std::istream& is,node& n) -> std::istream&
    {
        return is >> n.p >> n.c;
    }
    int p,c;
};

int n,h;
std::array<node,N> a;

fun scan()
{
    std::cin >> n >> h;
    std::copy_n(std::istream_iterator<node>{ std::cin },n,a.begin() + 1);
}

//dp[i][k] = min -> dp[i - 1][k] and dp[i][k - pi] + ci

fun solve()
{
    auto [p,c]{ a[1] };
    int sum{ ((h + p - 1) / p) * c };
    std::vector<int> dp(sum + 1);
    for(int j : std::views::iota(0,sum + 1))
    {
        dp[j] = (j / a[1].c) * a[1].p;
    }
    for(int i : std::views::iota(2,n + 1))
    {
        for(int j : std::views::iota(std::min(a[i].c,sum + 1),sum + 1))
        {
            dp[j] = std::max(dp[j],dp[j - a[i].c] + a[i].p);
        }
    }
    return std::distance(dp.begin(),std::ranges::find_if(dp,[](int val)
    {
        return val >= h;
    }));
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(scan);
    print("{}",std::invoke(solve));

    return 0;
}