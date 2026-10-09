

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
#include<concepts>

#define fun auto

using int8 = char;
using uint8 = unsigned char;
using int32 = int;
using uint32 = unsigned int;
using uint = uint32;
using int64 = long long;
using uint64 = unsigned long long;
using namespace std::views;

template<typename... Args>
fun print(const std::format_string<Args...> fmts,Args&&... args)
{
    std::cout << std::vformat(fmts.get(), std::make_format_args(args...));
}

template<typename T>
concept C_two_dimensional_array = requires(T array)
{
    typename std::remove_all_extents_t<T>;
    { array[0][0] } -> std::same_as<std::add_lvalue_reference_t<std::remove_all_extents_t<T>>>;
};

template<typename T>
concept STD_two_dimensional_array = requires(T array)
{
    typename T::value_type::value_type;
    { array[0][0] } -> std::same_as<std::add_lvalue_reference_t<typename T::value_type::value_type>>;
};

template<typename T>
concept two_dimensional_array = C_two_dimensional_array<T> or STD_two_dimensional_array<T>;

template<two_dimensional_array T>
fun scan(T& array,int n,int m)
{
    for(int i : iota(1,n + 1))
    {
        for(int j : iota(1,m + 1))
        {
            std::cin >> array[i][j];
        }
    }
}

constexpr static int INF{ 0x3f3f3f3f };

constexpr static int N{ 100 + 2 };

int f,v;
int a[N][N];
int dp[N][N];

// dp[i][j] i瓶放j花
// dp[i][j] = a[j][i] + max{ dp[i - 1][j - 1],dp[i - 2][j - 1],...,dp[j - 1][j - 1] }

fun solve()
{
    std::cin >> f >> v;
    scan(a,f,v);
    for(int i : iota(1,v + 1))
    {
        for(int j : iota(1,std::min(i,f) + 1))
        {
            dp[i][j] = a[j][i] + std::ranges::max(iota(j - 1,i) | transform([j](int i){ return dp[i][j - 1]; }));
        }
    }
    int ret{ std::ranges::max(iota(f,v + 1) | transform([](int i){ return dp[i][f]; })) };
    print("{}\n",ret);
    std::vector<int> path;
    for(int i{ v },it{ f }; v >= 1 and it; --i)
    {
        if(dp[i][it] == ret)
        {
            path.push_back(i);
            ret -= a[it--][i];
        }
    }
    std::ranges::copy(path | reverse,std::ostream_iterator<int>{ std::cout," " });
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}