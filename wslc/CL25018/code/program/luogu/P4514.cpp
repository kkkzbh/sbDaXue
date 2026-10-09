

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

#define fun auto
template<typename... Args>
fun print(const std::format_string<Args...> fmts,Args&&... args)
{
    if constexpr(sizeof...(Args))
    {
        std::cout << std::vformat(fmts.get(), std::make_format_args(std::forward<Args>(args)...));
    }
    else
    {
        std::cout << fmts.get();
    }
}

constexpr static int N{ 2048 + 2 };

int n,m;
std::array<std::array<int,N>,N> d1,d2,d3,d4;

fun add(int x,int y,int val)
{
    int v2{ val * x };
    int v3{ val * y };
    int v4{ val * x * y };
    for(int i{ x }; i <= n; i += i & -i)
    {
        for(int j{ y }; j <= m; j += j & -j)
        {
            d1[i][j] += val;
            d2[i][j] += v2;
            d3[i][j] += v3;
            d4[i][j] += v4;
        }
    }
}

fun add(int x1,int y1,int x2,int y2,int val)
{
    add(x1,y1,val);
    add(x1,y2 + 1,-val);
    add(x2 + 1,y1,-val);
    add(x2 + 1,y2 + 1,val);
}

fun sum(int x,int y) -> int
{
    int ret{};
    for(int i{ x }; i; i -= i & -i)
    {
        for(int j{ y }; j; j -= j & -j)
        {
            ret += (x + 1) * (y + 1) * d1[i][j];
            ret -= (y + 1) * d2[i][j];
            ret -= (x + 1) * d3[i][j];
            ret += d4[i][j];
        }
    }
    return ret;
}

fun sum(int x1,int y1,int x2,int y2) -> int
{
    return sum(x2,y2) - sum(x2,y1 - 1) - sum(x1 - 1,y2) + sum(x1 - 1,y1 - 1);
}

fun solve()
{
    char ch;
    std::cin >> ch;
    std::cin >> n >> m;
    while(std::cin >> ch)
    {
        int a,b,c,d;
        std::cin >> a >> b >> c >> d;
        if(ch == 'L')
        {
            int delta;
            std::cin >> delta;
            add(a,b,c,d,delta);
        }
        else
        {
            print("{}\n",sum(a,b,c,d));
        }
    }
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}