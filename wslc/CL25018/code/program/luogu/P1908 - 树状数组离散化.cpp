

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

using int8 = char;
using uint8 = unsigned char;
using int32 = int;
using uint32 = unsigned int;
using uint = uint32;
using int64 = long long;
using uint64 = unsigned long long;

constexpr static int N{ 500000 + 2 };

int n;
std::array<int,N> d;

fun add(int it,int val)
{
    while(it <= n)
    {
        d[it] += val;
        it += it & -it;
    }
}

fun sum(int it)
{
    int ret{};
    while(it)
    {
        ret += d[it];
        it -= it & -it;
    }
    return ret;
}

fun solve()
{
    std::cin >> n;
    std::vector<int> vec{ std::numeric_limits<int>::max() },a;
    vec.reserve(n + 1);
    a.reserve(n);
    std::copy_n(std::istream_iterator<int>{ std::cin },n,std::back_inserter(a));
    std::ranges::copy(a,std::back_inserter(vec));
    std::ranges::sort(vec | std::views::drop(1),std::greater<>{});
    auto r{ std::ranges::unique(vec) };
    vec.erase(std::ranges::begin(r),std::ranges::end(r));
    int64 ans{};
    for(const int val : a)
    {
        auto it{ std::ranges::upper_bound(vec,val,std::greater<>{}) };
        int dis{ static_cast<int>(std::distance(vec.begin(),it)) };
        ans += sum(dis - 1);
        add(dis,1);
    }

    print("{}",ans);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}