

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
#include<deque>
#include<queue>

#define fun auto

using int64 = long long;
using uint64 = unsigned long long;
using namespace std::views;

template<typename... Args>
fun print(const std::format_string<Args...> fmts,Args&&... args)
{
    std::cout << std::vformat(fmts.get(), std::make_format_args(args...));
}

template<typename T>
fun print(T&& arg)
{
    print("{}",arg);
}

fun println()
{
    print('\n');
}

template<typename... Args>
fun println(const std::format_string<Args...> fmts,Args&&... args)
{
    print(fmts,std::forward<Args>(args)...);
    println();
}

template<typename T>
fun println(T&& arg)
{
    println("{}",arg);
}

constexpr int INF{ 0x3f3f3f3f };

// n + (n / 2) + (n / 4) + ... + (1) ≈ 2n

template<typename It>
fun quick_select(It l,It m,It r) -> void
{
    if(r - l == 1) {
        return;
    }
    It lt{ l + 1 },i{ l + 1 },rt{ r - 1 };
    while(i <= rt) {
        if(*i == *l) {
            ++i;
        } else if(*i < *l) {
            std::swap(*lt++,*i++);
        } else {
            std::swap(*i,*rt--);
        }
    }
    std::swap(*l,*(lt - 1));
    if(m < lt) {
        quick_select(l,m,lt);
    } else if(m > rt) {
        quick_select(rt + 1,m,r);
    }
}

fun solve()
{
    int n,k;
    std::cin >> n >> k;
    std::vector<int> a;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,std::back_inserter(a));
    quick_select(a.begin(),a.begin() + k,a.end());
    println(a[k]);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}