

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

template<int MOD_ = M>
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
        index -= (index / MOD_) * MOD_;
        return dp[(index + MOD_) % MOD_];
    }

    int dp[MOD_][M][M];
};

std::string s1,s2;
int n,m,k;

// dp[i][x][j] s1的前i个字符取x个字串
// = dp[i - 1][x][j] + dp[i - 1][x - 1][j - 1] + dp[i - 2][x - 1][j - 2]
// dp[i][0][0] = 1  dp[i][x][0] = 0   dp[0][x][j] = 0  dp[i][0][j] = 0

compress_array<1> dp;
compress_array prefix;

fun solve()
{
    std::cin >> n >> m >> k >> s1 >> s2;
    std::ranges::for_each(dp,[](auto& arr){ arr[0][0] = 1; });
    std::ranges::for_each(prefix,[](auto& arr){ arr[0][0] = 1; });
    for(int i : std::views::iota(1,n + 1))
    {
        for(int j : std::views::iota(1,std::min(m,i) + 1))
        {
            prefix[i][j][0] = (prefix[i - 1][j - 1][0] + dp[i][j][0]) % MOD;
        }
    }
    for(int i : std::views::iota(1,n + 1))
    {
        for(int j : std::views::iota(1,std::min(m,i) + 1))
        {
            int len{};
            while(j > len and  s1[i - len - 1] == s2[j - len - 1])
            {
                ++len;
            }
            for(int x : std::views::iota(1,std::min(i,k) + 1))
            {
                dp[i][j][x] = dp[i - 1][j][x];
                dp[i][j][x] = ((static_cast<int64>(dp[i][j][x]) + prefix[i - 1][j - 1][x - 1] - (j > len ? prefix[i - len - 1][j - len - 1][x - 1] : 0)) + MOD) % MOD;
                prefix[i][j][x] = (prefix[i - 1][j - 1][x] + dp[i][j][x]) % MOD;
            }
        }
    }
    print("{}",dp[n][m][k]);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}
