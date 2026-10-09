

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

constexpr static int N{ 500000 + 2 };

int n,m;
std::array<int,N> a;

fun add(int i,int val)
{
    while(i <= n)
    {
        a[i] += val;
        i += i & -i;
    }
}

fun sum(int i)
{
    int ret{};
    while(i)
    {
        ret += a[i];
        i -= i & -i;
    }
    return ret;
}

fun query(int l,int r)
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
        add(i,val);
    }
    for(int i : std::views::iota(1,m + 1))
    {
        int o,x,y;
        std::cin >> o >> x >> y;
        if(o == 1)
        {
            add(x,y);
        }
        else
        {
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