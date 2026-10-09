

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
constexpr static int N{ 10000000 + 2 };
constexpr int null{};

int trie[N][2];
int pass[N];
int cnt{};

fun create() -> int
{
    trie[cnt][0] = trie[cnt][1] = null;
    pass[cnt] = INF;
    return cnt++;
}

fun insert(int val,int i)
{
    int it{ 1 };
    for(int k{ 29 }; k >= 0; --k)
    {
        int& t{ trie[it][val >> k & 1] };
        if(!t)
        {
            t = create();
        }
        it = t;
        pass[it] = std::min(pass[it],i);
    }
}

fun query(int a,int b) -> int
{
    int it{ 1 };
    int l{ INF },r{ INF };
    for(int k{ 29 }; k >= 0; --k)
    {
        int x{ a >> k & 1 };
        int y{ b >> k & 1 };
        if(y)
        {
            l = std::min(l,pass[trie[it][x]]);
        }
        else
        {
            r = std::min(r,pass[trie[it][x ^ 1]]);
        }
        if(trie[it][x ^ y] == null)
        {
            it = null;
            break;
        }
        it = trie[it][x ^ y];
    }
    l = std::min(l,pass[it]);   // the situation of equal
    r = std::min(r,pass[it]);
    if(l == INF or r == INF)
    {
        return -1;
    }
    else
    {
        return std::max({ 1,l - 1,r - 1 });
    }
}

// f = (a ^ x) - b = 0
// a ^ x = b
// x = a ^ b;
// 对每一位而言 如果 x = a ^ b 则该位是0
// 使f < 0的最小i解 为 从某位开始 低于b位的数字
// 反之同理

fun solve()
{
    int n,q;
    scan(n,q);
    cnt = 0;    // 清空
    create();   // 预留空结点
    create();
    for(int i{ 1 },val; i <= n; ++i)
    {
        std::cin >> val;
        insert(val,i);
    }
    for(int i{},a,b; i != q; ++i)
    {
        std::cin >> a >> b;
        println(query(a,b));
    }

}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}