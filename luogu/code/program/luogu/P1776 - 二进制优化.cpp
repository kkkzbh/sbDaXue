

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

constexpr static int N{ 40000 + 2 };

struct node
{
    int v,w;
};

int n,w;
std::vector<node> a;
std::array<int,N> dp;

fun scan()
{
    std::cin >> n >> w;
    for(int i : std::views::iota(0,n))
    {
        int value,weight,cnt;
        std::cin >> value >> weight >> cnt;
        for(int k{ 1 }; cnt >= k; k <<= 1)
        {
            a.emplace_back(k * value,k * weight);
            cnt -= k;
        }
        if(cnt)
        {
            a.emplace_back(cnt * value,cnt * weight);
        }
    }
}

fun solve()
{
    for(const auto [value,weight] : a)
    {
        for(int j : std::views::iota(std::min(weight,w + 1),w + 1) | std::views::reverse)
        {
            dp[j] = std::max(dp[j],dp[j - weight] + value);
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