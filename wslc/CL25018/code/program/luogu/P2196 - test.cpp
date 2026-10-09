

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

fun dfs(int i) -> int
{
    int val{};
    for(const int it : g[i])
    {
        val = std::max(dfs(it),val);
    }
    return val + a[i];
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    int val{ std::numeric_limits<int>::min() };
    for(int i{ 1 }; i <= n; ++i)
    {
        val = std::max(dfs(i),val);
    }
    print("{}",val);

    return 0;
}