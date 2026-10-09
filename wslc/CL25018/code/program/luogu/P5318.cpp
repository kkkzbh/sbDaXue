

#include<iostream>
#include<array>
#include<vector>
#include<algorithm>
#include<bitset>
#include<queue>

constexpr int M_size{ 100000 + 2 };

std::bitset<M_size> vis;
std::array<std::vector<int>,M_size> a;

void dfs(int i)
{
    vis.set(i);
    std::cout << i << ' ';
    for(auto&& it : a[i])
    {
        if(!vis[it])
            dfs(it);
    }
}

void bfs(int i)
{
    std::queue<int> que;
    std::cout << i << ' ';
    que.push(i);
    vis.set(i);
    while(!que.empty())
    {
        int val = que.front();
        for(auto&& it : a[val])
        {
            if(!vis[it])
            {
                que.push(it);
                vis.set(it);
                std::cout << it << ' ';
            }
        }
        que.pop();
    }
}

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    int n,m;
    std::cin >> n >> m;
    for(int i{ 1 }; i <= m; ++i)
    {
        int x,y;
        std::cin >> x >> y;
        a[x].push_back(y);
    }
    for(int i{ 1 }; i <= n; ++i)
    {
        std::sort(a[i].begin(),a[i].end());
    }
    dfs(1);
    vis.reset();
    std::cout << '\n';
    bfs(1);

    return 0;
}