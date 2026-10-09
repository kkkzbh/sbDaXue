

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
//#define print(...) std::cout << std::format(__VA_ARGS__)
template<typename... Args>
void print(const std::format_string<Args...> fmts,Args&&... args)
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
constexpr static int N2{ 1000 + 2 };

struct node
{
    int a,b;
};

int m,n,k;
std::array<std::vector<node>,N> a;
std::array<int,N2> dp;

fun scan()
{
    std::cin >> m >> n;
    for(int i : std::views::iota(0,n))
    {
        int x,y,z;
        std::cin >> x >> y >> z;
        a[z].emplace_back(x,y);
        k = std::max(z,k);
    }
}

// dp[i][j] = max -> dp[i - 1][j] dp[i - 1][j - wi] + vi...

fun solve()
{
    for(int i : std::views::iota(0,k + 1))
    {
        if(!a[i].empty())
        for(int j : std::views::iota(0,m + 1) | std::views::reverse)
        {
            for(auto [weight,value] : a[i])
            {
                if(j - weight >= 0)
                {
                    dp[j] = std::max(dp[j],value + dp[j - weight]);
                }
            }
        }
    }
    return dp[m];
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(scan);
    print("{}",std::invoke(solve));

    return 0;
}