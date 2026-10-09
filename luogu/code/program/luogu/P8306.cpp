

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

template<typename... Args>
fun println(const std::format_string<Args...> fmts,Args&&... args)
{
    std::cout << std::vformat(fmts.get(), std::make_format_args(args...)) << '\n';
}

fun println()
{
    std::cout << '\n';
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
constexpr static int N{ 3000000 + 2 };
constexpr int N2{ 26 + 26 + 10 };

int trie[N][N2];
int pass[N];
int end[N];
int cnt{ 1 };

fun cv(char c) -> int
{
    if(c > 96)
    {
        return c - 'a';
    }
    else if(c > 64)
    {
        return 25 + (c ^ 64);
    }
    else
    {
        return 52 + (c ^ 48);
    }
}

fun insert(const std::string& s)
{
    int it{};
    ++pass[it];
    for(const char c : s)
    {
        if(!trie[it][cv(c)])
        {
            trie[it][cv(c)] = cnt++;
        }
        it = trie[it][cv(c)];
        ++pass[it];
    }
    ++end[it];
}

fun query(const std::string& s)
{
    int it{};
    for(const char c : s)
    {
        if(!trie[it][cv(c)])
        {
            return 0;
        }
        it = trie[it][cv(c)];
    }
    return pass[it];
}

fun solve()
{
    int n,q;
    scan(n,q);
    for(int i : iota(0,n))
    {
        std::string s;
        scan(s);
        insert(s);
    }
    for(int i : iota(0,q))
    {
        std::string s;
        scan(s);
        println("{}",query(s));
    }
    for(int i : iota(0,cnt))
    {
        std::ranges::fill(trie[i],0);
    }
    std::ranges::fill_n(pass,cnt,0);
    std::ranges::fill_n(end,cnt,0);
    cnt = 1;
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while(t--)
    {
        std::invoke(solve);
    }
}