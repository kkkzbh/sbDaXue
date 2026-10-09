


#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<queue>
#include<bitset>
#include<algorithm>
#include<numeric>
#include<stack>
#include<utility>
#include<ranges>

constexpr static int N{ 50000 + 2 };

std::array<std::vector<int>,N> a;
int n;
std::array<int,N> sz,d;
std::bitset<N> vis;

void bfs(int i)
{
    std::queue<int> que;
    que.push(i);
    vis.set(i);
    int dis{};
    int level{ 1 };
    while(!que.empty())
    {
        for(int j{},cei = que.size(); j != cei; ++j)
        {
            int t{ que.front() };
            que.pop();
            for (const auto it: a[t])
            {
                if(!vis[it])
                {
                    que.push(it);
                    dis += level;
                    vis.set(it);
                }
            }
        }
        ++level;
    }
    d[i] = dis;
}

void size(int i,int pre)
{
    int sum{};
    for(const auto it : a[i])
    {
        if(it != pre)
        {
            size(it, i);
            sum += sz[it];
        }
    }
    sz[i] = sum + 1;
}

void dp(int i,int pre)
{
    if(pre)
    {
        d[i] = d[pre] + n - (sz[i] << 1);
    }
    for(const auto it : a[i])
    {
        if(it != pre)
        {
            dp(it, i);
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n;
    for(int i{ 1 }; i < n; ++i)
    {
        int x,y;
        std::cin >> x >> y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    bfs(1);
    size(1,0);
    dp(1,0);

    auto it{ std::ranges::min_element(d | std::views::drop(1) | std::views::take(n)) };

    std::cout << std::format("{} {}",it - d.begin(),*it);

    return 0;
}