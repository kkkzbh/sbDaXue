

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

using int64 = long long;

constexpr static int N{ 100000 + 2 };

int n,m;
std::array<int64,N> a,d1,d2;

fun add(int x,int val)
{
    int v2{ val * x };
    for(int i{ x }; i <= n; i += i & -i)
    {
        d1[i] += val;
        d2[i] += v2;
    }
}

fun add(int l,int r,int val)
{
    add(l,val);
    add(r + 1,-val);
}

fun sum(int x) -> int64
{
    int64 ret{};
    for(int i{ x }; i; i -= i & -i)
    {
        ret += (x + 1) * d1[i];
        ret -= d2[i];
    }
    return ret;
}

fun sum(int l,int r) -> int64
{
    return sum(r) - sum(l - 1);
}

fun solve()
{
    std::cin >> n >> m;
    for(int i : std::views::iota(1,n + 1))
    {
        int val;
        std::cin >> val;
        add(i,i,val);
    }
    for(int i : std::views::iota(0,m))
    {
        int o;
        std::cin >> o;
        if(o == 1)
        {
            int x,y,k;
            std::cin >> x >> y >> k;
            add(x,y,k);
        }
        else
        {
            int x,y;
            std::cin >> x >> y;
            print("{}\n",sum(x,y));
        }
    }
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}