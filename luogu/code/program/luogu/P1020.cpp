

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

std::vector<int> a;

fun solve()
{
    int val;
    while(std::cin >> val)
    {
        a.emplace_back(val);
    }

    if(a.empty())
    {
        print("0\n0");
        return;
    }

    std::vector<int> ends;
    for(const int v : a)
    {
        auto it{ std::ranges::upper_bound(ends,v,std::greater<>{}) };
        if(it == ends.end())
        {
            ends.push_back(v);
        }
        else
        {
            *it = v;
        }
    }

    std::vector<int> cnt;
    for(const int v : a)    // 实际行为等价为求解最长上升子序列
    {
        auto it{ std::ranges::lower_bound(cnt,v) };
        if(it == cnt.end())
        {
            cnt.push_back(v);
        }
        else
        {
            *it = v;
        }
    }

    print("{}\n{}",ends.size(),cnt.size());
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}