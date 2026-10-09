


#include<iostream>
#include<array>
#include<vector>
#include<bitset>
#include<queue>

constexpr int N{ 1000 + 2 };

int n,m;

std::array<std::vector<int>,N> a;
std::array<int,N> in;
std::bitset<N> vis;
std::array<std::bitset<N>,N> table;

int bfs()
{
    std::queue<int> que;
    int dis{};
    for(int i{ 1 }; i <= n; ++i)
        if(!in[i])
            que.push(i);
    while(!que.empty())
    {
        ++dis;
        for(int i{},cei{ que.size() }; i != cei; ++i)
        {
            int v = que.front();
            que.pop();
            for(auto&& it : a[v])
            {
                if(!--in[it])
                {
                    que.push(it);
                }
            }
        }
    }
    return dis;
}

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    std::cin >> n >> m;
    std::array<int,N> v;
    for(int i{ 1 }; i <= m; ++i)
    {
        int k;
        std::cin >> k;
        for(int j{ 1 }; j <= k; ++j)
        {
            std::cin >> v[j];
            vis.set(v[j]);
        }
        for(int j{ v[1] }; j <= v[k]; ++j)  //500 * 500 = 50000 * 1000 = 50000000 = 1e7
            if(!vis[j])
                for(int _{ 1 }; _ <= k; ++_)
                    if(!table[j][v[_]])
                    {
                        a[j].push_back(v[_]);
                        table[j].set(v[_]);
                        ++in[v[_]];
                    }
        vis.reset();
    }
    std::cout << bfs();

    return 0;
}