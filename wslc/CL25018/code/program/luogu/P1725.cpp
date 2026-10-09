

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
#include<deque>

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

constexpr static int N{ 200000 + 2 };
constexpr static int INF{ std::numeric_limits<int>::max() >> 1 };

int n,l,r;
std::array<int,N> a;
std::deque<int> que;

fun push(int it)
{
    while(!que.empty() and a[it] >= a[que.back()])
    {
        que.pop_back();
    }
    que.push_back(it);
}

fun pop(int it)
{
    if(que.front() == it)
    {
        que.pop_front();
    }
}

fun solve()
{
    std::cin >> n >> l >> r;
    std::copy_n(std::istream_iterator<int>{ std::cin },n + 1,a.begin());
    push(n + 1);
    for(int i : std::views::iota(0,n - l + 1) | std::views::reverse)
    {
        push(i + l);
        pop(i + r + 1);
        a[i] += a[que.front()];
    }

    print("{}",a[0]);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);


    return 0;
}