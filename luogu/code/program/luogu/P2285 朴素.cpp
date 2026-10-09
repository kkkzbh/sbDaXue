

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

constexpr static int N{ 10000 + 2 };

struct node
{
    fun friend operator>>(std::istream& is,node& n) -> std::istream&
    {
        return is >> n.t >> n.x >> n.y;
    }
    int t,x,y;
};

int n,m;
std::array<node,N> a;
std::array<int,N> dp;

// dp[i] = max dp[j(j < i and 能转移(距离与时间差))]

fun solve()
{
    std::cin >> n >> m;
    std::copy_n(std::istream_iterator<node>{ std::cin },m,a.begin() + 1);
    auto distance = [](int i,int j)
    {
        return std::abs(a[i].x - a[j].x) + std::abs(a[i].y - a[j].y);
    };
    for(int i : std::views::iota(1,m + 1))
    {
        for(int j : std::views::iota(1,i))
        {
            if(a[i].t - a[j].t >= distance(i,j))
            {
                dp[i] = std::max(dp[i],dp[j]);
            }
        }
        dp[i] += 1;
    }
    print("{}",std::ranges::max(std::views::counted(dp.begin() + 1,m)));
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);


    return 0;
}