

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
constexpr static int N{ 400 + 2 };
constexpr static int Delta{ 400000 };
constexpr static int N2{ 800000 + 2 };

struct node
{
    fun friend operator>>(std::istream& is,node& n) -> std::istream&
    {
        return is >> n.s >> n.f;
    }
    int s,f;
};

template<typename T,int N,int Del_>
struct marray
{
    fun operator[](int i) -> T&
    {
        return a[i + Del_];
    }
    T a[N]{};
};

template<typename T,int N>
struct carray
{
    fun operator[](int i) -> T&
    {
        return a[i % N];
    }
    T a[N]{};
};

int n;
node a[N];
int t;
// dp[i][j] = max{ dp[i - 1][j],f + dp[i - 1][j - s] }

carray<marray<int,N2,Delta>,2> dp;

fun solve()
{
    scan(n);
    //scan(a,n);
    int as{},af{};
    for(auto [s,f] : istream<node>(std::cin) | take(n))
    {
        if(s >= 0 and f >= 0)
        {
            as += s;
            af += f;
        }
        else if(s >= 0 or f >= 0)
        {
            a[++t] = { s,f };
        }
    }

    int mins{},maxs{};
    for(int i : iota(1,t + 1))
    {
        if(a[i].s > 0)
        {
            maxs += a[i].s;
        }
        else
        {
            mins += a[i].s;
        }
    }

    memset(&dp,~0x3f,sizeof(dp));
    dp[0][0] = 0;
    for(int i : iota(1,n + 1))
    {
        for(int j : iota(mins,maxs + 1))
        {
            dp[i][j] = std::ranges::max(dp[i - 1][j],dp[i - 1][j - a[i].s] + a[i].f);
        }
    }
    int val{};
    for(int j : iota(-as,maxs + 1))
    {
        if(dp[n][j] >= 0)
        {
            val = std::max(val,dp[n][j] + j);
        }
    }
    print("{}",val + as + af);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}