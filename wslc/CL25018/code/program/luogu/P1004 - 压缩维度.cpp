

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
#include<bitset>
#include<unordered_map>

using int8 = char;
using uint8 = unsigned char;
using int32 = int;
using uint32 = unsigned int;
using uint = uint32;
using int64 = long long;
using uint64 = unsigned long long;

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

constexpr static int N{ 9 + 2 };
constexpr static int N2{ (9 << 1) + 2 };

struct input_data
{
    fun friend operator>>(std::istream& is,input_data& n) -> std::istream&
    {
        return is >> n.x >> n.y >> n.v;
    }
    int x,y,v;
};

int n;
std::array<std::array<int,N>,N> a;
std::array<std::array<std::array<int,N>,N>,N2> dp;

fun solve()
{
    std::cin >> n;
    for(const auto [x,y,v] : std::views::istream<input_data>(std::cin) | std::views::take_while([](const auto& v){ return v.x and v.y and v.v; }))
    {
        a[x][y] = v;
    }
    // y = k + 2 - x
    dp[0][1][1] = a[1][1];
    for(int k : std::views::iota(1,(n << 1) - 1))
    {
        for(int x1 : std::views::iota(1,n + 1))
        {
            for(int x2 : std::views::iota(1,n + 1))
            {
                dp[k][x1][x2] = std::max({
                                                 dp[k - 1][x1][x2],
                                                 dp[k - 1][x1 - 1][x2],
                                                 dp[k - 1][x1][x2 - 1],
                                                 dp[k - 1][x1 - 1][x2 - 1],
                                         });
                if(x1 == x2)
                {
                    dp[k][x1][x2] += a[x1][k + 2 - x1];
                }
                else
                {
                    dp[k][x1][x2] += a[x1][k + 2 - x1] + a[x2][k + 2 - x2];
                }
            }
        }
    }

    print("{}",dp[(n << 1) - 2][n][n]);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}