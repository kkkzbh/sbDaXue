

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

#define fun auto

using int8 = char;
using uint8 = unsigned char;
using int32 = int;
using uint32 = unsigned int;
using uint = uint32;
using int64 = long long;
using uint64 = unsigned long long;
using std::views::iota;

template<typename... Args>
fun print(const std::format_string<Args...> fmts,Args&&... args)
{
    std::cout << std::vformat(fmts.get(), std::make_format_args(args...));
}

constexpr static int INF{ 0x3f3f3f3f };

constexpr static int N{ 100 + 2 };

int f,v;
int a[N][N];

// dp[i 花瓶][j 花朵][放了没有] // 前i个瓶子 第j朵花 是否放了第i个瓶子
//                                              dp[i - 1][j][false]
// dp[i][j][false] = dp[i][j - 1][true] or dp[i - 1][j - 1][true] or dp[i - 2][j - 1][true] ... or d[j - 1][j - 1][true]
// dp[i][j][true] = dp[i - 1][j - 1][true] or d[i - 2][j - 1][true] or dp[i - 3][j - 1][true] ... or dp[j - 1][j - 1][true]  + vi
//                          dp[i - 1][j][false]
// dp[i - 1][j][false] = dp[i - 1][j - 1][true] or dp[i - 2][j - 1][true] or ... dp[j - 1][j - 1][true] max
// dp

int dp[N][N][2];

fun solve()
{
    std::cin >> f >> v;
    std::ranges::for_each(std::views::counted(std::ranges::begin(a) + 1,f),[](auto& arr)
    {
        std::copy_n(std::istream_iterator<int>{ std::cin },v,std::ranges::begin(arr) + 1);
    });

    dp[1][1][true] = a[1][1];
    dp[1][2][false] = dp[1][1][true];
    for(int i : std::views::iota(2,v + 1))
    {
        dp[i][1][false] = dp[i - 1][1][false];
        dp[i][1][true] = a[1][i];
        int cei{ std::min(i,f) + 1 };
        for(int j : std::views::iota(2,cei))
        {
            dp[i][j][false] = std::max(dp[i][j - 1][true],dp[i - 1][j][false]);
            dp[i][j][true] = dp[i - 1][j][false] + a[j][i];
        }
        dp[i][cei][false] = dp[i][cei - 1][true];
    }
    auto proj = [](int i){ return dp[i][f][true]; };
    int val{ proj(std::ranges::max(std::views::iota(f,v + 1),std::less<>{},proj)) };
    print("{}\n",val);
    std::vector<int> vec;
    int it{ f };
    for(int i : std::views::iota(1,v + 1) | std::views::reverse)
    {
        if(dp[i][it][true] == val)
        {
            val -= a[it][i];
            vec.push_back(i);
            if(!--it) { break; }
        }
    }
    std::ranges::copy(vec | std::views::reverse,std::ostream_iterator<int>{ std::cout," " });
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}