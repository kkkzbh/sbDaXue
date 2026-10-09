

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
#include<deque>

#define fun auto
#define print(...) std::cout << std::format(__VA_ARGS__)

constexpr static int N{ 100000 + 2 };

namespace std
{
    fun operator>>(std::istream &is, std::array<int, 2> &a) -> std::istream&
    {
        return is >> a[0] >> a[1];
    }
}

std::array<std::array<int,2>,N> a;
int n,d;
std::deque<int> maxque,minque;

fun push(int it)
{
    while(!maxque.empty() and a[it][1] >= a[maxque.back()][1])
    {
        maxque.pop_back();
    }
    while(!minque.empty() and a[it][1] <= a[minque.back()][1])
    {
        minque.pop_back();
    }
    maxque.push_back(it);
    minque.push_back(it);
}

fun pop(int it)
{
    if(maxque.front() == it)
    {
        maxque.pop_front();
    }
    if(minque.front() == it)
    {
        minque.pop_front();
    }
}

#define MAX a[maxque.front()][1]
#define MIN a[minque.front()][1]

fun scan()
{
    std::cin >> n >> d;
    std::copy_n(std::istream_iterator<std::array<int,2>>{ std::cin },n,a.begin() + 1);
}

fun solve()
{
    std::ranges::sort(std::views::counted(a.begin() + 1, n), [](const auto x, const auto y)
    {
        return x[0] < y[0];
    });
    int ret{ std::numeric_limits<int>::max() };
    for(int l{ 1 },r{ 1 }; r <= n; ++r)
    {
        push(r);
        while(!maxque.empty() and MAX - MIN >= d)
        {
            ret = std::min(ret,a[r][0] - a[l][0]);
            pop(l++);
        }
    }
    print("{}",ret == std::numeric_limits<int>::max() ? -1 : ret);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    solve();

    return 0;
}