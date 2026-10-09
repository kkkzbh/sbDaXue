

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

constexpr static int N{ 100 + 2 };

std::array<std::bitset<N>,N> a;

fun solve()
{
    int n;
    std::cin >> n;
    int cnt{};
    for(int i : std::views::iota(0,n))
    {
        int x,y;
        std::cin >> x >> y;
        if(a[x][y])
        {
            cnt += 4;
        }
        else
        {
            cnt += a[x - 1][y] + a[x][y - 1] + a[x + 1][y] + a[x][y + 1];
        }
        a[x][y] = true;
    }
    print("{}",(n << 1) - 0.5 * cnt);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}