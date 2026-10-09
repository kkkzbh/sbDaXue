

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
std::array<int64,N> a,d,id;

fun add(int i,int val,auto& v)
{
    while(i <= n)
    {
        v[i] += val;
        i += i & -i;
    }
}

fun sum(int i,auto& v) -> int64
{
    int64 ret{};
    while(i)
    {
        ret += v[i];
        i -= i & -i;
    }
    return ret;
}

fun add(int l,int r,int val)
{
    add(l,val,d);
    add(r + 1,-val,d);
    add(l,l * val,id);
    add(r + 1,-(r + 1) * val,id);
}

fun query(int l,int r) -> int64
{
    return (r + 1) * sum(r,d) - sum(r,id) - l * sum(l - 1,d) + sum(l - 1,id);
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
            print("{}\n",query(x,y));
        }
    }
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}