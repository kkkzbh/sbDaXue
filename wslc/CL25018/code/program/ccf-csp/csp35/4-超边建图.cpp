

#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto a = std::vector(n,std::make_pair(0,0));
    for(auto& [x,y] : a) {
        std::cin >> x >> y;
    }
    auto b = std::vector(m,std::make_tuple(0,0,0,0));
    for(auto& [x,y,r,t] : b) {
        std::cin >> x >> y >> r >> t;
    }
    auto contain = std::vector(m,std::vector<int>{});
    for(auto i = 0; i != m; ++i) {
        auto const& [x,y,r,t] = b[i];
        for(auto j = 0; j != n; ++j) {
            auto const& [px,py] = a[j];
            if(px >= x - r and px <= x + r and py >= y - r and py <= y + r) {
                contain[i].push_back(j);
            }
        }
    }
    auto g = std::vector(n + m,std::vector<std::pair<int,int>>{});
    for(auto i = 0; i != m; ++i) {
        auto const& [x,y,r,t] = b[i];
        for(auto j : contain[i]) {
            g[n + i].emplace_back(j,t);
            g[j].emplace_back(n + i,0);
        }
    }

    auto que = std::invoke([&] {
        using node = std::pair<int,int>;
        auto proj = [](node const& nd) {
            return std::get<1>(nd);
        };
        auto cmp = [proj,cmp = std::greater{}](node const& lhs,node const& rhs) {
            return cmp(proj(lhs),proj(rhs));
        };
        using namespace __gnu_pbds;
        using que_t = priority_queue<node,decltype(cmp)>;
        return que_t{ cmp };
    });

    auto constexpr INF = std::numeric_limits<int>::max() / 2;
    auto dis = std::vector(n + m,INF);
    auto qit = std::vector(n + m,decltype(que)::point_iterator{});
    for(auto i = 0; i != n + m; ++i) {
        qit[i] = que.push({ i,INF });
    }
    dis[0] = 0;
    que.modify(qit[0],{ 0,dis[0] });
    while(not que.empty()) {
        auto [it,d] = que.top();
        que.pop();
        for(auto const& [i,w] : g[it]) {
            if(dis[it] + w < dis[i]) {
                dis[i] = dis[it] + w;
                que.modify(qit[i],{ i,dis[i] });
            }
        }
    }

    if(dis[n - 1] == INF) {
        std::cout << "Nan";
        return 0;
    }
    std::cout << dis[n - 1];

}