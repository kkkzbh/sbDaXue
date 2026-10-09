

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

constexpr static int len{ 40 + 2 };
constexpr static int N{ 100000 + 2 };
constexpr static int INF{ std::numeric_limits<int>::max() >> 1 };

std::string s;
int n;
std::array<std::array<int,len>,len> value;
std::array<std::array<int,N>,len> dp;

fun solve()
{
    std::cin >> s >> n;
    for(int i : std::views::iota(0,static_cast<int>(s.size())))
    {
        for(int j : std::views::iota(i + 1,static_cast<int>(s.size()) + 1))
        {
            if((value[i][j] = value[i][j - 1] * 10 + (s[j - 1] ^ 48)) > n)
            {
                std::ranges::fill(value[i].begin() + j + 1,value[i].begin() + s.size() + 1,INF);
                break;
            }
        }
    }

    // dp[i][k] = min -> dp[j][k - 这段数字] + 1
    std::ranges::for_each(dp | std::views::take(s.size() + 1),[](auto& v){ std::ranges::fill_n(v.begin(),n + 1,INF); });
    dp[0][0] = -1;
    for(int i : std::views::iota(1,static_cast<int>(s.size()) + 1))
    {
        for(int k : std::views::iota(0,n + 1))
        {
            for(int j : std::views::iota(0,i) | std::views::reverse | std::views::filter([=](int j){ return k >= value[j][i]; }))
            {
                dp[i][k] = std::min(dp[i][k], dp[j][k - value[j][i]] + 1);
            }
        }
    }

    print("{}",dp[s.size()][n] == INF ? -1 : dp[s.size()][n]);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}