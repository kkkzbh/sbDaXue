#pragma once

#include<iostream>
#include<array>
#include<vector>
#include<queue>
#include<algorithm>

constexpr int M_size{ 10000 + 2 };

struct node
{
    int v;
    int weigh;
    node() = default;
    node(int v,int w) : v(v),weigh(v){}
};

std::array<std::vector<int>,M_size> a;
std::array<int,M_size> id;
std::array<int,M_size> w;
std::array<std::size_t,M_size> dist;
int n;

void top_sort()
{
    std::queue<int> que;
    que.push(0);
    dist[0] = 0;
    while(!que.empty())
    {
        int v = que.front();
        for(auto&& it : a[v])
        {
            if(dist[v] + w[it] > dist[it])
                dist[it] = dist[v] + w[it];
            if(!--id[it])
                que.push(it);
        }
        que.pop();
    }
}

int main()
{
    std::cin >> n;
    for(int i{ 1 }; i <= n; ++i)
    {
        int x,y;
        std::cin >> x >> y;
        w[x] = y;
        int c;
        while(std::cin >> c)
        {
            a[c].push_back(x);
            ++id[x];
            if(!c)
                break;
        }
    }
    top_sort();
    std::size_t ans{};
    for(int i{ 1 }; i <= n; ++i)
        ans = std::max(ans,dist[i]);
    std::cout << ans;

    return 0;
}