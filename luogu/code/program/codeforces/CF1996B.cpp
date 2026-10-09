

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

constexpr static int N{ 1000 + 2 };

int n,k;
std::array<std::string,N> a;

fun solve()
{
    std::cin >> n >> k;
    std::copy_n(std::istream_iterator<std::string>{ std::cin },n,a.begin() + 1);

    for(int i{ 1 }; i <= n; i += k)
    {
        for(int j{}; j < n; j += k)
        {
            print("{}",a[i][j]);
        }
        print("\n");
    }
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int _;
    std::cin >> _;
    while(_--)
    {
        std::invoke(solve);
    }

    return 0;
}