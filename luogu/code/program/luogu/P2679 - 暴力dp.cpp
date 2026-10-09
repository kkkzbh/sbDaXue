

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

constexpr static int N{ 1000 + 2 };
constexpr static int M{ 200 + 2 };
constexpr static int MOD{ 1000000007 };

struct compress_array
{
    auto begin()
    {
        return std::ranges::begin(dp);
    }
    auto end()
    {
        return std::ranges::end(dp);
    }
    auto& operator[](int index)
    {
        index -= (index / MOD) * MOD;
        return dp[(index + MOD) % MOD];
    }

    constexpr static int MOD{ M + 100 };

    int dp[MOD][M][M];
};

std::string s1,s2;
int n,m,k;

// dp[i][x][j] s1的前i个字符取x个字串
// = dp[i - 1][x][j] + dp[i - 1][x - 1][j - 1] + dp[i - 2][x - 1][j - 2]
// dp[i][0][0] = 1  dp[i][x][0] = 0   dp[0][x][j] = 0  dp[i][0][j] = 0

compress_array dp;

fun solve()
{
    std::cin >> n >> m >> k >> s1 >> s2;
    std::ranges::for_each(dp,[](auto& arr){ arr[0][0] = 1; });
    for(int i : std::views::iota(1,n + 1))
    {
        for(int j : std::views::iota(1,std::min(m,i) + 1))
        {
            for(int x : std::views::iota(1,std::min(i,k) + 1))
            {
                dp[i][x][j] = dp[i - 1][x][j];
                for(int len{ 1 }; j >= len and  s1[i - len] == s2[j - len]; ++len)
                {
                    dp[i][x][j] += dp[i - len][x - 1][j - len];
                    dp[i][x][j] %= MOD;
                }
            }
        }
    }
    print("{}",dp[n][k][m]);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}