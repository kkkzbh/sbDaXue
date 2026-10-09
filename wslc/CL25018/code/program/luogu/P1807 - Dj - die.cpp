



#include<iostream>
#include<format>
#include<string_view>


template<typename... Args>
__attribute__((always_inline))
void print(const std::string_view fmt_str,Args&&... args)
{
    fputs(std::vformat(fmt_str,std::make_format_args(args...)).data(),stdout);
}


__attribute__((always_inline))
void print(char c)
{
    fputc(c,stdout);
}


__attribute__((always_inline))
void print(const std::string_view s)
{
    fputs(s.data(),stdout);
}


template<typename Value>
__attribute__((always_inline))
void print(Value&& i)
{
    print("{}",i);
}


template<typename... Args>
__attribute__((always_inline))
void println(Args&&... args)
{
    print(args...);
    fputc('\n',stdout);
}


__attribute__((always_inline))
void println()
{
    fputc('\n',stdout);
}


struct M_System
{
    struct M_Out
    {
        template<typename... Args>
        __attribute__((always_inline))
        void println(Args&&... args) const
        {
            ::println(args...);
        }


        template<typename... Args>
        __attribute__((always_inline))
        void print(Args&&... args) const
        {
            ::print(args...);
        }


        __attribute__((always_inline))
        void println()
        {
            fputc('\n',stdout);
        }
    };
    M_Out out;
}System;

#include<array>
#include<vector>
#include<utility>
#include<queue>
#include<bitset>

constexpr int M_size{ 1500 + 2 };

int n,m;
std::array<std::vector<std::pair<int,int>>,M_size> a;
std::array<int,M_size> dist;
std::bitset<M_size> vis;

auto Pre = []() -> auto
{
    dist.fill( -1147483648);
    return 0;
}();

void Dijkstra()
{
    std::priority_queue
            <std::pair<int,int>,std::vector<std::pair<int,int>>,
                    decltype([](const auto& e1,const auto& e2) -> bool
                    {
                        return e1.second < e2.second;
                    })>
            que;
    dist[1] = 0;
    que.emplace(1,dist[1]);
    while(!que.empty())
    {
        int v = que.top().first;
        que.pop();
        if(!vis[v])
        {
            vis.set(v);
            for(auto&& it : a[v])
            {
                if(!vis[it.first] && dist[v] + it.second > dist[it.first])
                {
                    dist[it.first] = dist[v] + it.second;
                    que.emplace(it.first,dist[it.first]);
                }
            }
        }
    }
}

int main()
{
    std::cin >> n >> m;
    for(int i{ 1 }; i <= m; ++i)
    {
        int u,v,w;
        std::cin >> u >> v >> w;
        a[u].emplace_back(v,w);
    }
    Dijkstra();
    System.out.print(dist[n]);

    return 0;
}