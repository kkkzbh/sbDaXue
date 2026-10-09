

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
    { array[0] } -> std::same_as<std::add_lvalue_reference<typename T::value_type>>;
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

template<Integral T>
fun constexpr lg2(T n) noexcept -> int
{
    int log{};
    if constexpr(sizeof(T) >= 8)
    { if (n >= T{ 1 } << 32) { n >>= 32; log += 32; } }
    if constexpr(sizeof(T) >= 4)
    { if (n >= T{ 1 } << 16) { n >>= 16; log += 16; } }
    if constexpr(sizeof(T) >= 2)
    { if (n >= T{ 1 } << 8) { n >>= 8; log += 8; } }
    if (n >= T{ 1 } << 4) { n >>= 4; log += 4; }
    if (n >= T{ 1 } << 2) { n >>= 2; log += 2; }
    if (n >= T{ 1 } << 1) { log += 1; }
    return log;
}

template<Integral T>
struct fenwick
{

    explicit fenwick(int n) noexcept : a(std::vector<T>(n)) {}

    fun add(int i,T v) noexcept
    {
        for(; i <= a.size(); i += i & -i)
        {
            a[i - 1] += v;
        }
    }

    fun sum(int i) const noexcept -> T
    {
        T ret{};
        for(; i; i -= i & -i)
        {
            ret += a[i - 1];
        }
        return ret;
    }

    fun sum(int l,int r) const noexcept -> T
    {
        return sum(r) - sum(l - 1);
    }

    fun select(T k) const noexcept -> int = delete;

    std::vector<T> a;
};

fun solve()
{
    int n;
    scan(n);
    std::vector<int> a,inva(n);
    a.reserve(n);
    std::copy_n(std::istream_iterator<int>{ std::cin },n,std::back_inserter(a));
    for(int i : iota(0,n)) {
        --a[i];
        inva[a[i]] = i;
    }
    int64 ans{};
    std::vector<std::vector<int>> g(n);
    for(int i : iota(0,n)) {
        int t{ std::min(i,a[i] ? inva[a[i] - 1] + 1 : 0 ) };
        g[t].push_back(i);
    }
    fenwick<int> fw{ n };
    for(int i : iota(0,n)) {
        for (int j: g[i]) {
            fw.add(a[j] + 1, 1);
        }

        for(int k: iota(1,n + 1)) {
            print("{} ",fw.sum(k,k));
        }
        println();
        std::cout << std::flush;

        fw.add(a[i] + 1, -1);

        for(int k: iota(1,n + 1)) {
            print("{} ",fw.sum(k,k));
        }
        println();
        std::cout << std::flush;

        ans += std::max(0, fw.sum(i ? a[i - 1] + 2 : 1, a[i] + 1));
    }
    print(ans);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}