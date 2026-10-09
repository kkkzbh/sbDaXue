


#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<queue>
#include<bitset>
#include<algorithm>
#include<numeric>

constexpr static int N{ 50000 + 2 };

std::array<std::vector<int>,N> a;
int n;
std::bitset<N> vis;

int bfs(int i)
{
    std::queue<int> que;
    que.push(i);
    vis.set(i);
    int dis{};
    int level{ 1 };
    while(!que.empty())
    {
        for(int i{},cei = que.size(); i != cei; ++i)
        {
            int t{que.front()};
            que.pop();
            for (const auto it: a[t])
            {
                if (!vis[it])
                {
                    que.push(it);
                    vis.set(it);
                    dis += level;
                }
            }
        }
        ++level;
    }
    vis.reset();
    return dis;
}

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n;
    for(int i{ 1 }; i <= n; ++i)
    {
        int x,y;
        std::cin >> x >> y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    int ansi{};
    int ans{ std::numeric_limits<int>::max() };
    for(int i{ 1 }; i <= n; ++i)
    {
        if(int val{ bfs(i) }; val < ans)
        {
            ans = val;
            ansi = i;
        }
    }
    std::cout << std::format("{} {}",ansi,ans);

    return 0;
}