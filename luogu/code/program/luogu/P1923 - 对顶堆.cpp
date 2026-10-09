

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

fun solve()
{
    int n,k;
    std::cin >> n >> k;
    std::vector<int> a;
    a.reserve(n);
    std::copy_n(std::istream_iterator<int>{ std::cin },n,std::back_inserter(a));
    std::priority_queue<int> maxque; // 1,2,3,
    std::priority_queue<int> minque; // a[k],x,x,x,x....
    ++k;
    for(int v : a)
    {
        if(maxque.size() < k) {
            maxque.push(v);
        } else if(v < maxque.top()) {
            minque.push(maxque.top());
            maxque.pop();
            maxque.push(v);
        } else {
            minque.push(v);
        }
    }
    println(maxque.top());
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}