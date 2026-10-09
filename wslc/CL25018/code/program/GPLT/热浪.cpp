

#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>

using namespace std::views;

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,c,first,end;
    std::cin >> n >> c >> first >> end;
    --first,--end;
    auto a = std::vector(n,std::vector<std::pair<int,int>>{});
    for(auto i : iota(0,c)) {
        int x,y,w;
        std::cin >> x >> y >> w;
        --x,--y;
        a[x].emplace_back(y,w);
        a[y].emplace_back(x,w);
    }

    auto dijkstra = std::invoke([&] noexcept {
        using namespace __gnu_pbds;
        using node = int;
        auto constexpr INF = std::numeric_limits<int>::max();
        auto dis = std::vector(n,INF);
        auto vis = std::vector(n,false);
        dis[first] = 0;
        auto cmp = [&](node x,node y) {
            return dis[x] > dis[y];
        };
        auto que = priority_queue<node,decltype(cmp)>{ cmp };
        auto qit = std::vector(n,decltype(que)::point_iterator{});
        for(auto i : iota(0,n)) {
            qit[i] = que.push(i);
        }
        while(not que.empty()) {
            auto it = que.top();
            que.pop();
            vis[it] = true;
            if(it == end) {
                break;
            }
            for(auto [i,w] : a[it] | filter([&](auto const& p) {
                auto const& [i,w] = p;
                return not vis[i] and dis[it] + w < dis[i];
            })) {
                dis[i] = dis[it] + w;
                que.modify(qit[i],i);
            }
        }
        return dis[end];
    });
    std::cout << dijkstra;

}