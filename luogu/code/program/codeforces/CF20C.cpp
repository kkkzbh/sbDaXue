
#include<iostream>
#include<array>
#include<vector>
#include<bitset>
#include<stack>
#include<queue>
#include<utility>

constexpr int M_size{ 100000 + 2 };
constexpr std::size_t INF{ static_cast<std::size_t>(-1) };

struct node
{
    int v;
    int weigh;
    node() = default;
    node(int v,int w) : v(v),weigh(w){}
};

std::bitset<M_size> vis;
std::array<std::vector<node>,M_size> a;
std::array<std::size_t,M_size> dist;
std::array<int,M_size> path;
int n,m;    // n is the size of point   m is the size of side

auto Pre = []() -> auto
{
    dist.fill(INF);
    return 0;
}();

#ifdef LINEAR

void Dijkstra(int i)
{
    dist[i] = 0;
    std::size_t dis{};
    while(dis != INF)
    {
        vis.set(i);
        for(auto&& it : a[i])
        {
            if(!vis[it.v] && dist[i] + it.weigh < dist[it.v])
            {
                dist[it.v] = dist[i] + it.weigh;
                path[it.v] = i;
            }
        }
        dis = INF;
        for(int j{ 1 }; j <= n; ++j)
        {
            if(!vis[j] && dist[j] < dis)
            {
                dis = dist[j];
                i = j;
            }
        }
    }
}

#else

void Dijkstra(int i)
{
    std::priority_queue
            <std::pair<int,int>,std::vector<std::pair<int,int>>,
                    decltype([](const std::pair<int,int>& e1,const std::pair<int,int>& e2) -> bool
                    {
                        return e1.second > e2.second;
                    })>
            que;
    dist[i] = 0;
    que.emplace(i,dist[i]);
    while(!que.empty())
    {
        int v = que.top().first;
        que.pop();
        if(!vis[v])
        {
            vis.set(v);
            for(auto&& it : a[v])
            {
                if(!vis[it.v] && dist[v] + it.weigh < dist[it.v])
                {
                    dist[it.v] = dist[v] + it.weigh;
                    path[it.v] = v;
                    que.emplace(it.v,dist[it.v]);
                }
            }
        }
    }
}

#endif

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    std::cin >> n >> m;
    for(int i{ 1 }; i <= m; ++i)
    {
        int u,v,w;
        std::cin >> u >> v >> w;
        a[u].emplace_back(v,w);
        a[v].emplace_back(u,w);
    }
    Dijkstra(1);
    std::stack<int> stk;
    int k = n;
    if(path[k])
    {
        stk.push(k);
        while(path[k])
            stk.push(k = path[k]);
        while(!stk.empty())
        {
            std::cout << stk.top() << ' ';
            stk.pop();
        }
    }
    else
        std::cout << -1;

    return 0;
}