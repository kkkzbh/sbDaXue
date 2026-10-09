

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

using int64 = long long;
using uint64 = unsigned long long;
using namespace std::views;

template<typename T>
concept STD_array = requires(T array)
{
    typename T::value_type;
    { array[0] } -> std::same_as<std::add_lvalue_reference_t<typename T::value_type>>;
};

template<typename T>
concept Array = STD_array<T> or std::is_array_v<T>;

#ifdef __GNUC__
template<typename T>
concept Integral = std::is_integral_v<T> or std::is_same_v<T,__int128>;
#else
template<typename T>
concept Integral = std::is_integral_v<T>;
#endif

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

constexpr int INF{ 0x3f3f3f3f };

fun solve()
{
    std::array<int,6> a;
    scan(a,5);
    int64 ans{};
    int k{ std::min(a[5],a[1]) };
    a[1] -= k;
    a[5] -= k;
    ans += k;
    k = std::min(a[4],a[2]);
    a[2] -= k;
    a[4] -= k;
    ans += k;
    ans += a[3] / 2;
    a[3] %= 2;
    if(a[5]) // 1 用完了 剩5
    {
        ans += a[3];
        a[5] -= a[3];
        a[3] = 0;
        int it{ a[2] ? 2 : 4 };
        if(a[it] >= a[5])
        {
            ans += a[5] + (a[it] - a[5]) / 3;
        }
        else
        {
            ans += (a[it] + a[5]) / 2;
        }
    }
    else    // 5 没了 有2,3,4 可能有1 ---1,2,3,4
    {
        if(a[4])    // 2 没了 3,4 可能有1
        {
            if(a[1] >= a[4] * 2)
            {
                ans += (a[1] + 3ll * a[3] + 4ll * a[4]) / 6;
            }
            else
            {
                ans += (a[1] + a[3] + a[4]) / 3;
            }
        }
        else  //只可能剩1,2,3
        {
            ans += (a[1] + 2ll * a[2] + 3ll * a[3]) / 6;
        }
    }
    println(ans);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    scan(t);
    while(t--)
    {
        std::invoke(solve);
    }
}