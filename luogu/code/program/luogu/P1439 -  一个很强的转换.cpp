

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

constexpr static int N{ 100000 + 2 };

int n;
std::array<int,N> a,b,map;

fun solve()
{
    std::cin >> n;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin() + 1);
    std::copy_n(std::istream_iterator<int>{ std::cin },n,b.begin() + 1);
    for(int i : std::views::iota(1,n + 1))
    {
        map[a[i]] = i;
    }
    std::vector<int> ends;
    for(int i : std::views::iota(1,n + 1))
    {
        auto it{ std::ranges::upper_bound(ends,map[b[i]]) };
        if(it == ends.end())
        {
            ends.push_back(map[b[i]]);
        }
        else
        {
            *it = map[b[i]];
        }
    }

    print("{}",ends.size());
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}