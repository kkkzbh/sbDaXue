

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
constexpr static int N{ 100000 + 2 };

struct node
{
    fun friend operator>>(std::istream& is,node& n) -> std::istream&
    {
        return is >> n.a >> n.b >> n.c >> n.d;
    }
    int a,b,c,d;
};

int n;
node a[N];

fun solve()
{
    scan(n);
    scan(a,n);
    std::vector<int> red,white;
    for(int i : iota(1,n + 1))
    {
        auto [x,b,c,d]{ ::a[i] };
        if(c and d)
        {
            if(x < b)
            {
                red.push_back(i);
            }
            else
            {
                white.push_back(i);
            }
        }
        else if(c)
        {
            red.push_back(i);
        }
        else
        {
            white.push_back(i);
        }
    }
    std::ranges::sort(red,std::less<>{},[](int i){ return a[i].a; });
    std::ranges::sort(white,std::less<>{},[](int i){ return a[i].b; });
    print("{}",red.size());
    for(int val : red)
    {
        print(" {}",val);
    }
    print("\n{}",white.size());
    for(int val : white)
    {
        print(" {}",val);
    }
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}