

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
#include<queue>

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

constexpr static int N{ 100000 + 2 };
constexpr static int N2{ 200000 + 2 };

struct node
{
    int pos;
    int i;
};

int n;
std::array<std::vector<int>,N2> g;
std::bitset<N> vis;
std::array<std::vector<int>,N> g2;
std::array<int,N> ind;

fun dfs(int it) -> int
{
    int max{};
    for(const int i : g[it])
    {
        max = std::max(dfs(i),max);
    }
    return max + 1;
}

constexpr static bool DFS{ false };

fun depth(int start)
{
    if constexpr(DFS)
    {
        return dfs(start);
    }
    else
    {
        std::queue<int> que;
        que.push(start);
        int depth{};
        while (!que.empty())
        {
            ++depth;
            for (int i{static_cast<int>(que.size())}; i--;)
            {
                int it{que.front()};
                que.pop();
                for (const int v: g[it])
                {
                    que.push(v);
                    vis.set(v);
                }
            }
        }
        return depth;
    }
}

fun top_sort(int start)
{
    std::queue<int> que;
    vis.set(start);
    que.push(start);
    while(!que.empty())
    {
        int it{ que.front() };
        que.pop();
        for(const auto i : g2[it])
        {
            if(!--ind[i])
            {
                vis.set(i);
                que.push(i);
            }
        }
    }
}

fun solve()
{
    std::cin >> n;
    for(int i : std::views::iota(1,n + 1))
    {
        int v;
        std::cin >> v;
        g[v].push_back(i);
        g2[i].push_back(v);
        if(v <= n)
        {
            ++ind[v];
        }
    }
    int ret{};
    for(int i : std::views::iota(n + 1,(n << 1) + 1))
    {
        ret += depth(i) - 1;
    }
    for(int i : std::views::iota(1,n + 1) | std::views::filter([](const int i){ return !vis[i] and !ind[i]; }))
    {
        top_sort(i);
    }
    for(int i : std::views::iota(1,n + 1))
    {
        ret += !vis[i] and ind[i];
    }

    print("{}",ret);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);

    return 0;
}