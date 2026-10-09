

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
constexpr static double DNF{ 1e10 };
constexpr static double eps{ 1e-6 };

struct point
{
    int x,y;
};

struct line
{
    point a;
    point b;
};

int x,y,r,vx,vy;
int lx,ly,rx,ry;

int cross(point a,point b)
{
    return a.x * b.y - a.y * b.x;
}

bool is_intersect(const line& a,const line& b)
{
    auto& [as,ae]{ a };
    auto& [bs,be]{ b };
    point dira{ ae.x - as.x,ae.y - as.y };
    point dirb{ bs.x - be.x,bs.y - be.y };
    point dir{ bs.x - as.x,bs.y - as.y };
    int d{ cross(dira,dirb) };
    if(d == 0)  // 两线段平行
    {
        if(cross(dir,dira)) // 两线段在一条直线上
        {
            return false;
        }
        return std::max(as.x,ae.x) >= std::min(bs.x,be.x) and std::max(bs.x,be.x) >= std::min(as.x,ae.x);
    }
    double t{ cross(dir,dirb) / static_cast<double>(d) };
    double u{ cross(dira,dir) / static_cast<double>(d) };
    return t >= -eps and t <= 1 + eps and u >= -eps and u <= 1 + eps;
}

fun solve()
{
    scan(x,y,r,vx,vy,lx,ly,rx,ry);
    line m[] {
            {{ lx + r,ly + r },{ rx - r,ly + r }},
            {{ lx + r,ly + r },{ lx + r,ry - r }},
            {{ lx + r,ry - r },{ rx - r,ry - r }},
            {{ rx - r,ly + r },{ rx - r,ry - r }}
    };
    line l{{ x,y },{ x + 10000000 * vx , y + 10000000 * vy }};
    bool tag{};
    for(const line& it : m)
    {
        tag |= is_intersect(l,it);
    }
    if(tag)
    {
        print("Yes\n");
    }
    else
    {
        print("No\n");
    }
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