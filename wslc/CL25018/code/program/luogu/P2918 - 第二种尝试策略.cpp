

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
        return is >> n.p >> n.c;
    }
    int p,c;
};

constexpr static int N{ 100 + 2 };
constexpr static int INF{ std::numeric_limits<int>::max() >> 1 };

int n,h;
std::array<node,N> a;

fun scan()
{
    std::cin >> n >> h;
    std::copy_n(std::istream_iterator<node>{ std::cin },n,a.begin() + 1);
}

fun solve()
{
    int k{ h + std::ranges::max(std::views::counted(a.begin() + 1,n),std::less<>{},[](const node n){ return n.p; }).p };
    std::vector<int> dp(k + 1);
    std::ranges::fill(dp | std::views::drop(1),INF);
    for(int i : std::views::iota(1,n + 1))
    {
        for(int j : std::views::iota(a[i].p,k))
        {
            dp[j] = std::min(dp[j],dp[j - a[i].p] + a[i].c);
        }
    }
    return std::ranges::min(dp | std::views::drop(h));
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(scan);
    print("{}",std::invoke(solve));


    return 0;
}