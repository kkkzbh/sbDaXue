

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
std::array<int,N> a,b;

fun add(int i,int val)
{
    while(i <= n)
    {
        b[i] += val;
        i += i & -i;
    }
}

fun sum(int i)
{
    int ret{};
    while(i)
    {
        ret += b[i];
        i -= i & -i;
    }
    return ret;
}

fun solve()
{
    std::cin >> n >> m;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin() + 1);
    for(int i : std::views::iota(0,m))
    {
        int o;
        std::cin >> o;
        if(o == 1)
        {
            int x,y,k;
            std::cin >> x >> y >> k;
            add(x,k);
            add(y + 1,-k);
        }
        else
        {
            int x;
            std::cin >> x;
            print("{}\n",sum(x) + a[x]);
        }
    }
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}