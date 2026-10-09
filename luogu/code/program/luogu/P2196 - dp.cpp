

#include<iostream>
#include<format>
#include<array>
#include<algorithm>
#include<iterator>
#include<ranges>
#include<vector>

#define fun auto
#define print(...) std::cout << std::format(__VA_ARGS__)

constexpr static int N{ 20 + 2 };

std::array<int,N> a;
std::array<std::vector<int>,N> g;
int n;
std::array<int,N> path;

fun scan() -> void
{
    std::cin >> n;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin() + 1);
    for(int i{ 1 },val; i <= n; ++i)
    {
        for(int j{ i + 1 }; j <= n; ++j)
        {
            std::cin >> val;
            if(val)
            {
                g[i].push_back(j);
            }
        }
    }
}

fun fdp()
{
    for(int i{ n - 1 }; i; --i)
    {
        int sec{};
        for(const int it : g[i])
        {
            if(!sec or a[sec] < a[it])
            {
                sec = it;
            }
        }
        path[i] = sec;
        a[i] += a[sec];
    }
}

fun put()
{
    int pos{ static_cast<int>(std::ranges::max_element(a | std::views::drop(1)) - a.begin()) };
    print("{}",pos);
    for(int it{ path[pos] }; it; it = path[it])
    {
        print(" {}",it);
    }
    print("\n{}",a[pos]);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    fdp();
    put();

    return 0;
}