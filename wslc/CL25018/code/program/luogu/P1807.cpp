

#include<iostream>
#include<array>
#include<queue>

// 本题关键在于 必须从1开始 然后废除 那些入度为0的非1节点对 其他入度的影响
//  dp dp dp !!!
// 下面算法虽然AC的 但是并不完美 如果某些入度为0的非1点 去其影响时 出现了 新的入度为0的非1点 依然需要去除
//                                                  为什么？ dp思想是很显然的
//                                 如果你出现了循环完一次 觉得应该再次重复循环一次判断 陷入无限的这种
//                                                  那么应思考是否可以dp 以递推的方式完成这个工作

using ll = long long;

constexpr int M_size{ 1500 + 2 };
constexpr int M_size2{ 50000 + 2 };
constexpr int null{ -1 };
constexpr ll M_minst{ -222147482648 };

std::array<int,M_size> a;   //pointer which point a tuple that can use it as index to visit value
std::array<int,M_size2> next;
std::array<int,M_size2> to;
std::array<int,M_size2> weigh;
std::array<ll,M_size> dist;
std::array<int,M_size> id;
int top{ 0 };
int n,m;

[[maybe_unused]]
auto Pre = []() -> auto
{
    a.fill(null);
    dist.fill(M_minst);
    return 0;
}();

void push(int u,int v,int w)
{
    to[top] = v;
    next[top] = a[u];
    weigh[top] = w;
    a[u] = top++;
    ++id[v];
}

void top_sort(int i)
{
    std::queue<int> que;
    que.push(i);
    dist[i] = 0;
    while(!que.empty())
    {
        int v = que.front();
        for(int it{ a[v] }; it != null; it = next[it])
        {
            if(dist[v] + weigh[it] > dist[to[it]])
                dist[to[it]] = dist[v] + weigh[it];
            if(!--id[to[it]])
                que.push(to[it]);
        }
        que.pop();
    }
}

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    std::cin >> n >> m;
    for(int i{ 1 }; i <= m ; ++i)
    {
        int x,y,z;
        std::cin >> x >> y >> z;
        push(x,y,z);
    }
    for(int i{ 2 }; i <= n; ++i)
    {
        if(!id[i])
        {
            for(int it{ a[i] }; it != null; it = next[it])
            {
                --id[to[it]];
            }
        }
    }
    top_sort(1);

    if(dist[n] == M_minst)
        std::cout << -1;
    else
        std::cout << dist[n];

    return 0;
}