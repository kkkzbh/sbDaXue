

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
    std::cout << std::vformat(fmts.get(), std::make_format_args(args...));
}

constexpr static int N{ 1000 + 2 };
constexpr static int INF{ 2147483647 };

std::string s;

// dp[i][j] = 一样就是 dp[i + 1][j - 1] 否则就是 dp[i][j - 1] dp[i + 1][j]取最小值

int dp[N];

fun solve()
{
    std::cin >> s;
    for(int j : std::views::iota(1,static_cast<int>(s.size())))
    {
        int ld{ dp[j + 1] };
        for(int i : std::views::iota(0,j + 1) | std::views::reverse)
        {
            int tmp{ dp[i] };
            if(s[i] == s[j])
            {
                dp[i] = ld;
            }
            else
            {
                dp[i] = std::min(dp[i],dp[i + 1]) + 1;
            }
            ld = tmp;
        }
    }
    print("{}",dp[0]);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}