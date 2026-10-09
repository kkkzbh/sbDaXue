

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

struct node
{
    fun friend operator>>(std::istream& is,node& n) -> std::istream&
    {
        return is >> n.v >> n.w >> n.m;
    }
    int v,w,m;
};

constexpr static int N{ 100 + 2 };
constexpr static int N2{ 40000 + 2 };

int n,w;
std::array<node,N> a;
std::array<int,N2> dp;

fun scan()
{
    std::cin >> n >> w;
    std::copy_n(std::istream_iterator<node>{ std::cin },n,a.begin() + 1);
}

fun solve()
{
    for(int i : std::views::iota(1,n + 1))
    {
        for(int j : std::views::iota(a[i].w,w + 1) | std::views::reverse)
        {
            for(int k : std::views::iota(1,std::min(a[i].m,j / a[i].w) + 1))
            {
                dp[j] = std::max(dp[j],dp[j - k * a[i].w] + k * a[i].v);
            }
        }
    }
    print("{}",dp[w]);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(scan);
    std::invoke(solve);

    return 0;
}