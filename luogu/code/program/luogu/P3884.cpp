

#include<iostream>
#include<array>
#include<vector>
#include<algorithm>
#include<queue>

constexpr size_t M_size{ 100 + 2 };

std::array<std::vector<int>,M_size> g;
std::array<bool,M_size> vis;
std::array<std::array<bool,M_size>,M_size> isf;

int depth(int root)
{
    int d{};
    vis[root] = true;
    for(auto&& i : g[root])
    {
        if(!vis[i])
        {
            isf[i][root] = true;
            d = std::max(d,depth(i));
        }
    }
    return d + 1;
}

int width(int root)
{
    std::queue<int> que;
    que.push(root);
    vis[root] = true;
    int width{};
    while(!que.empty())
    {
        int sz = que.size();
        width = std::max(width,sz);
        for(int i{}; i != sz; ++i)
        {
            int it = que.front();
            for(auto&& i : g[it])
            {
                if(!vis[i])
                {
                    que.push(i);
                    vis[i] = true;
                }
            }
            que.pop();
        }
    }
    return width;
}

bool flag;
int d;
int tmp;
void dis(int x,int y)
{
    if(x == y) 
    {
        flag = true;
        d = tmp;
    }
    if(flag) return;
    vis[x] = true;
    for(auto&& i : g[x])
    {
        if(!vis[i])
        {
            tmp += 1 + isf[x][i];
            dis(i,y);
            tmp -= 1 + isf[x][i]; 
        }
    }
    vis[x] = false;
}

int main()
{
    freopen("../in.in","r",stdin);
    freopen("../out.out","w",stdout);
    int n;
    std::cin >> n;
    int root = 1;
    for(int i{ 1 },u,v; i != n;++i)
    {
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int x,y;
    std::cin >> x >> y;
    std::cout << depth(root) << '\n';
    vis.fill(0);
    std::cout << width(root) << '\n';
    vis.fill(0);
    dis(x,y);
    std::cout << d;

    return 0;
}