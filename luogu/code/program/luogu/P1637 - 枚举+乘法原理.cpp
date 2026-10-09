

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
    if constexpr(sizeof...(Args))
    {
        std::cout << std::vformat(fmts.get(), std::make_format_args(std::forward<Args>(args)...));
    }
    else
    {
        std::cout << fmts.get();
    }
}

struct bitree
{
    std::vector<int> a;

    explicit bitree(uint64 n) : a(std::vector<int>(n + 1)){}

    fun add(int i,int val)
    {
        while(i < a.size())
        {
            a[i] += val;
            i += i & -i;
        }
    }

    fun sum(int i) -> int
    {
        int ret{};
        while(i)
        {
            ret += a[i];
            i -= i & -i;
        }
        return ret;
    }
};

int n;
std::vector<int> a;

fun solve()
{
    std::cin >> n;
    a.reserve(n);
    std::copy_n(std::istream_iterator<int>{ std::cin },n,std::back_inserter(a));
    std::vector<int> vec;
    vec.reserve(n + 1);
    vec.push_back(std::numeric_limits<int>::min());
    std::ranges::copy(a,std::back_inserter(vec));
    std::ranges::sort(vec);
    auto ukr{ std::ranges::unique(vec) };
    vec.erase(ukr.begin(),ukr.end());

    bitree b{ vec.size() - 1 };
    std::vector<int> lns;
    for(const int val : a)
    {
        auto it{ std::ranges::lower_bound(vec,val) };
        int index{ static_cast<int>(std::distance(vec.begin(),it)) };
        lns.push_back(b.sum(index - 1));
        b.add(index,1);
    }
    std::ranges::fill(b.a,0);
    int64 ans{};
    for(const int i : std::views::iota(0,n) | std::views::reverse)
    {
        auto it{ std::ranges::lower_bound(vec,a[i]) };
        int index{ static_cast<int>(vec.size() - std::distance(vec.begin(),it)) };
        ans += lns[i] * b.sum(index - 1);
        b.add(index,1);
    }
    print("{}",ans);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}