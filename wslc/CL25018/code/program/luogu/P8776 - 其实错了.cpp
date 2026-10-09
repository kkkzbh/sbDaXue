

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
#include<unordered_set>

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

std::array<int,N> a;
int n,k;

fun scan()
{
    std::cin >> n >> k;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin() + 1);
}

fun solve() -> int
{
    std::vector<int> ends;
    auto proj{ [](const int i){ return a[i]; } };
    for(int i : std::views::iota(1,n + 1))
    {
        auto it{ std::ranges::upper_bound(ends,a[i],std::less<>{},proj) };
        if(it == std::ranges::end(ends))
        {
            ends.push_back(i);
        }
        else
        {
            *it = i;
        }
    }
    std::unordered_set<int> set{ ends.begin(),ends.end() };
    int ret{};
    int val{};
    for(int i : std::views::iota(1,n + 1))
    {
        if(set.contains(i))
        {
            val = 0;
        }
        else
        {
            ++val;
            ret = std::max(ret,val);
        }
    }
    return ends.size() + (ret <= k ? ret : k);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(scan);
    int ret{ std::invoke(solve) };
    print("{}",ret);

    return 0;
}