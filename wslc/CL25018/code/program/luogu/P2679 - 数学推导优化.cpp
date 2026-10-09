

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

template<typename T,int MOD_>
struct carray
{
    fun begin() noexcept
    {
        return std::ranges::begin(a);
    }
    fun end() noexcept
    {
        return std::ranges::end(a);
    }
    fun operator[](int i)
    {
        return a[i % MOD_];
    }

    T a[MOD_];
};

int n,m,k;
std::string s1,s2;

carray<int[M][M],2> dp;

fun solve()
{
    std::cin >> n >> m >> k >> s1 >> s2;
    dp[0][0][0] = dp[1][0][0] = 1;
    dp[1][1][1] = s1[0] == s2[0];
    for(int i{ 2 }; i <= n; ++i)
    {
        for(int j{ std::min(i,m) }; j >= 1; --j)
        {
            for(int x{ std::min(i,k) }; x >= 1; --x)
            {
                if(s1[i - 1] == s2[j - 1])
                {
                    dp[i][j][x] = (static_cast<int64>(dp[i - 1][j][x]) + dp[i - 1][j - 1][x - 1] + dp[i - 1][j - 1][x] - dp[i - 2][j - 1][x] + MOD) % MOD;
                }
                else
                {
                    dp[i][j][x] = dp[i - 1][j][x];
                }
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