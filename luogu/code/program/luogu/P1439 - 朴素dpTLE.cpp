

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

constexpr static int N{ 100000 + 2 };

int n;
std::array<int,N> a,b;
std::array<int,N> dp;

fun solve()
{
    std::cin >> n;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin() + 1);
    std::copy_n(std::istream_iterator<int>{ std::cin },n,b.begin() + 1);

    /*
     *  dp[i][j] = if equal -> 1 + dp[i - 1][j - 1]
     *  else max -> dp[i][j - 1] | dp[i - 1][j]
     */
    for(int i : std::views::iota(1,n + 1))
    {
        int leftup{ dp[0] };
        for(int j : std::views::iota(1,n + 1))
        {
            int tmp{ dp[j] };
            if(a[i] == b[j])
            {
                dp[j] = leftup + 1;
            }
            else
            {
                dp[j] = std::max(dp[j],dp[j - 1]);
            }
            leftup = tmp;
        }
    }

    print("{}",dp[n]);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}