

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
#include<deque>

#define fun auto

using int8 = char;
using uint8 = unsigned char;
using int32 = int;
using uint32 = unsigned int;
using uint = uint32;
using int64 = long long;
using uint64 = unsigned long long;
using namespace std::views;

template<typename T>
concept STD_array = requires(T array)
{
    typename T::value_type;
    { array[0] } -> std::same_as<std::add_lvalue_reference<typename T::value_type>>;
};

template<typename T>
concept Array = STD_array<T> or std::is_array_v<T>;

template<typename T>
concept Integral = std::convertible_to<T,int>;

template<typename... Args>
fun print(const std::format_string<Args...> fmts,Args&&... args)
{
    std::cout << std::vformat(fmts.get(), std::make_format_args(args...));
}

template<typename T>
fun print(T&& arg)
{
    print("{}",arg);
}

fun println()
{
    print('\n');
}

template<typename... Args>
fun println(const std::format_string<Args...> fmts,Args&&... args)
{
    print(fmts,std::forward<Args>(args)...);
    println();
}

template<typename T>
fun println(T&& arg)
{
    println("{}",arg);
}

template<Array T>
fun scan(T& array,int n)
{
    if constexpr(std::is_array_v<T>)
    {
        std::copy_n(std::istream_iterator<std::remove_all_extents_t<T>>{ std::cin },n, std::ranges::begin(array) + 1);
    }
    else
    {
        std::copy_n(std::istream_iterator<typename T::value_type>{ std::cin },n,array.begin() + 1);
    }
}

template<Array T,Integral... Args>
fun scan(T& array,int n,Args... args)
{
    for(int i : iota(1,n + 1))
    {
        scan(array[i],args...);
    }
}

template<typename... Args>
fun scan(Args&... args)
{
    (std::cin >> ... >> args);
}

constexpr static int INF{ 0x3f3f3f3f };
constexpr static int N{ 1000 + 2 };

int n,m;
char a[N][N];

// 枚举结尾,O(n) 然后 1,0,2,3,3,2... 一个区间,区间长度 * 区间最小值的最大值
// 一个窗口,如果这个数比区间最小值要大，加进来,否则,弹出左边的值,继续比较,每次要弹出时,收集答案
// 从i开头,最长的连续F数, if == ' F ' dp[i] = d[i - 1] + 1,否则 dp[i] = 0;
// 2 1 2

std::array<int,N> dp;

fun solve()
{
    scan(n,m);
    scan(a,n,m);
    int ans{};
    dp[m + 1] = -INF + 1;
    dp[0] = -INF;
    for(int i : iota(1,n + 1)) {
        for(int j : iota(1,m + 1)) {
            if(a[i][j] == 'F') {
                dp[j] += 1;
            } else {
                dp[j] = 0;
            }
        }
        std::vector<int> stk;
        stk.push_back(0);
        for(int j{ 1 },cei{ m + 1 }; j <= cei; ++j)
        {
            while(dp[j] <= dp[stk.back()]) {
                int k{ stk.back() };
                stk.pop_back();
                ans = std::max(ans,dp[k] * (j - stk.back() - 1));
            }
            stk.push_back(j);
        }
    }
    println(ans * 3);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}
