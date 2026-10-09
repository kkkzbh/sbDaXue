

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
//#define print(...) std::cout << std::format(__VA_ARGS__)
template<typename... Args>
void print(const std::format_string<Args...> fmts,Args&&... args)
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

int n,k;
std::array<int,N> a;

fun scan()
{
    std::cin >> n >> k;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin() + 1);
}

fun solve()
{
    std::vector<int> ends;
    std::vector<int> re(n + 2);
    for(int i : std::views::iota(1,n + 1) | std::views::reverse)
    {
        auto it{ std::ranges::upper_bound(ends,a[i],std::greater<>{}) };
        re[i] = static_cast<int>(std::distance(ends.begin(),it) + 1);
        if(it == std::ranges::end(ends))
        {
            ends.push_back(a[i]);
        }
        else
        {
            *it = a[i];
        }
    }
    ends.clear();
    int ret{};
    for(int l{ 1 },r{ k + 1 },cei{ n + 1 }; r <= cei; ++l,++r) // k + x == n + 1
    {
        auto it{ std::ranges::upper_bound(ends,a[r]) };
        ret = std::max(ret,re[r] + static_cast<int>(std::distance(ends.begin(),it)));
        it = std::ranges::upper_bound(ends,a[l]);
        if(it == ends.end())
        {
            ends.push_back(a[l]);
        }
        else
        {
            *it = a[l];
        }
    }
    return ret + k;
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(scan);
    print("{}",std::invoke(solve));

    return 0;
}