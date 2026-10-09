

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
constexpr static int N{ 500 + 2 };
constexpr char ans[][5]{ "No","Yes" };

char a[N][N];
bool vis[N][N];
int n,m;

fun solve() -> bool
{
    memset(&a,0,sizeof(a));
    memset(&vis,0,sizeof(vis));
    scan(n,m);
    scan(a,n,m);
    if(a[1][m] == '.')
    {
        int cnt{};
        for(int i : iota(1,n + 1))
        {
            for(int j : iota(1,m + 1))
            {
                if(a[i][j] == '.')
                {
                    ++cnt;
                }
                if(cnt == 2)
                {
                    return false;
                }
            }
        }
        int c{};
        for(int i : iota(1,n + 1))
        {
            for(int j : iota(1,m + 1))
            {
                if(a[i][j] == 'C')
                {
                    int t{};
                    if(!vis[i - 1][j] and a[i - 1][j] == 'D')
                    {
                        vis[i - 1][j] = true;
                        ++t;
                    }
                    if(!vis[i + 1][j] and a[i + 1][j] == 'U')
                    {
                        vis[i + 1][j] = true;
                        ++t;
                    }
                    if(!vis[i][j - 1] and a[i][j - 1] == 'R')
                    {
                        vis[i][j - 1] = true;
                        ++t;
                    }
                    if(!vis[i][j + 1] and a[i][j + 1] == 'L')
                    {
                        vis[i][j + 1] = true;
                        ++t;
                    }
                    if(t != 2)
                    {
                        return false;
                    }
                    c += 3;
                }
            }
        }
        return c == n * m - 1;
    }

    return false;
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while(t--)
    {
        print("{}\n",ans[std::invoke(solve)]);
    }
}