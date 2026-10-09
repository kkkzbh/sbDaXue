

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
constexpr static char ans[][5]{ "No","Yes" };
enum
{
    left_up = 0,
    right_up = 1,
    left_down = 2,
    right_down = 3,
};

fun constexpr pow2(int i) -> int
{
    return 1 << i;
}

int n,m;
char a[N][N];

// left_up -> right_up,

fun dirction(int x,int y,int dx,int dy) -> int
{
    if(dx <= x) // up
    {
        if(dy <= y) // left
        {
            return left_up;
        }
        else
        {
            return right_up;
        }
    }
    else    // down
    {
        if(dy <= y)
        {
            return left_down;
        }
        else
        {
            return right_down;
        }
    }
}

fun dfs(int x,int y,int dx,int dy,int k) -> void
{
    if(!k)
    {
        return;
    }
    int dir{ dirction(x,y,dx,dy) };
    int mv{ pow2(k - 2) };
    if(dir == left_up)
    {
        a[x + 1][y + 1] = left_up;
        dfs(x - mv,y - mv,dx,dy,k - 1);
        dfs(x - mv,y + mv,x,y + 1,k - 1);
        dfs(x + mv,y - mv,x + 1,y,k - 1);
        dfs(x + mv,y + mv,x + 1,y + 1,k - 1);
    }
    else if(dir == right_up)
    {
        a[x + 1][y] = right_up;
        dfs(x - mv,y - mv,x,y,k - 1);
        dfs(x - mv,y + mv,dx,dy,k - 1);
        dfs(x + mv,y - mv,x + 1,y,k - 1);
        dfs(x + mv,y + mv,x + 1,y + 1,k - 1);
    }
    else if(dir == left_down)
    {
        a[x][y + 1] = left_down;
        dfs(x - mv,y - mv,x,y,k - 1);
        dfs(x - mv,y + mv,x,y + 1,k - 1);
        dfs(x + mv,y - mv,dx,dy,k - 1);
        dfs(x + mv,y + mv,x + 1,y + 1,k - 1);
    }
    else
    {
        a[x][y] = right_down;
        dfs(x - mv,y - mv,x,y,k - 1);
        dfs(x - mv,y + mv,x,y + 1,k - 1);
        dfs(x + mv,y - mv,x + 1,y,k - 1);
        dfs(x + mv,y + mv,dx,dy,k - 1);
    }
}

fun solve()
{
    memset(&a,0xff,sizeof(a));
    scan(n,m);
    if(n != m or (n - (n & -n) or(m - (m & -m))))
    {
        print("No\n");
        return;
    }
    print("Yes\n");


    int val{ n };
    int k{};
    while((val >>= 1))
    {
        ++k;
    }

    int start{ pow2(k - 1) };
    dfs(start,start,1,m,k);
    for(int i : iota(1,n + 1))
    {
        for(int j : iota(1,m + 1))
        {
            switch(a[i][j])
            {
                case left_up :
                    a[i][j] = 'C';
                    a[i][j - 1] = 'R';
                    a[i - 1][j] = 'D';
                    break;
                case right_up:
                    a[i][j] = 'C';
                    a[i][j + 1] = 'L';
                    a[i - 1][j] = 'D';
                    break;
                case left_down:
                    a[i][j] = 'C';
                    a[i][j - 1] = 'R';
                    a[i + 1][j] = 'U';
                    break;
                case right_down:
                    a[i][j] = 'C';
                    a[i][j + 1] = 'L';
                    a[i + 1][j] = 'U';
                    break;
                default:
                    break;
            }
        }
    }
    a[1][m] = '.';
    for(int i : iota(1,n + 1))
    {
        for(int j : iota(1,m + 1))
        {
            print("{}",a[i][j]);
        }
        print("\n");
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