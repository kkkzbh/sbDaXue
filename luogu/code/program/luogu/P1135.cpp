


#include<iostream>
#include<array>
#include<queue>
#include<algorithm>
constexpr int size = 200 + 10;

int n,a,b;
std::array<int,size> k;
int ans{-1};
std::array<int,size> dis;

void bfs()
{
    std::queue<int> que;
    que.push(a);
    dis[a] = 0;
    while(!que.empty())
    {
        int v = que.front();
        if(v == b) break;
        if(v + k[v] <= n && dis[v + k[v]] == -1) que.push(v + k[v]),dis[v + k[v]] = dis[v] + 1;
        if(v - k[v] >= 0 && dis[v - k[v]] == -1) que.push(v - k[v]),dis[v - k[v]] = dis[v] + 1;
        que.pop();
    }
}

int main()
{
    std::cin >> n >> a >> b;
    for(int i = 1; i <= n;++i) std::cin >> k[i];
    std::fill(dis.begin() + 1,dis.begin() + 1 + n,-1);
    bfs();
    std::cout << dis[b];

    return 0;
}
