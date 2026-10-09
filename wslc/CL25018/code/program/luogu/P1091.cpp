

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
#include<unordered_map>

using int8 = char;
using uint8 = unsigned char;
using int32 = int;
using uint32 = unsigned int;
using uint = uint32;
using int64 = long long;
using uint64 = unsigned long long;



#define fun auto
template<typename... Args>
fun print(const std::format_string<Args...> fmts,Args&&... args)
{
    std::cout << std::vformat(fmts.get(), std::make_format_args(args...));
}

constexpr static int N{ 100 + 2 };

int n;
int a[N],lans[N];

fun solve()
{
    std::cin >> n;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,std::ranges::begin(a) + 1);
    std::vector<int> ends;
    for(int i : std::views::iota(1,n + 1))
    {
        auto it{ std::ranges::lower_bound(ends,a[i]) };
        if(it == ends.end())
        {
            ends.push_back(a[i]);
            lans[i] = ends.size();
        }
        else
        {
            *it = a[i];
            lans[i] = std::distance(ends.begin(),it);
        }
    }
    ends.clear();
    int sz{};
    for(int i : std::views::iota(1,n + 1) | std::views::reverse)
    {
        sz = std::max<int>(sz,lans[i] + ends.size());
        auto it{ std::ranges::lower_bound(ends,a[i]) };
        if(it == ends.end())
        {
            ends.push_back(a[i]);
        }
        else
        {
            *it = a[i];
        }
    }
    print("{:d}",n - sz);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}