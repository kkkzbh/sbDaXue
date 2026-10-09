

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

constexpr static int N{ 1000000 + 2 };
constexpr static auto null{ std::make_pair(2147483647,-2147483648) };
constexpr static int cei{ 1000000 };

int n,d;
std::array<std::pair<int,int>,N> a;
std::deque<int> minque,maxque;

fun operator==(const auto p1,const auto p2) -> bool
{
    return p1.first == p2.first and p1.second == p2.second;
}

fun push(int it)
{
    while(!minque.empty() and a[it].first <= a[minque.back()].first)
    {
        minque.pop_back();
    }
    while(!maxque.empty() and a[it].second >= a[maxque.back()].second)
    {
        maxque.pop_back();
    }
    minque.push_back(it);
    maxque.push_back(it);
}

fun pop(int it)
{
    if(!minque.empty() and it == minque.front())
    {
        minque.pop_front();
    }
    if(!maxque.empty() and it == maxque.front())
    {
        maxque.pop_front();
    }
}

fun scan()
{
    std::cin >> n >> d;
    std::ranges::fill(a,null);
    for(int i : std::views::iota(0,n))
    {
        int x,y;
        std::cin >> x >> y;
        a[x].first = std::min(a[x].first,y);
        a[x].second = std::max(a[x].second,y);
    }
}

fun ok(int mid) -> bool
{
    maxque.clear();
    minque.clear();
    for (int l{},r{}; r <= cei; ++r)
    {
        if (a[r] != null)
        {
            push(r);
        }
        if(int len{ r - l + 1 }; len == mid)
        {
            if(!maxque.empty() and a[maxque.front()].second - a[minque.front()].first >= d)
            {
                return true;
            }
            else
            {
                pop(l++);
            }
        }
    }
    return false;
}

fun solve()
{
    int ret{};
    int left{},right{ cei + 1 };
    while(left != right)
    {
        int mid{ (left + right) >> 1 };
        if(ok(mid))
        {
            ret = right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }
    return ret - 1;
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    print("{}",solve());


    return 0;
}