

#include <bits/stdc++.h>

auto main() -> int
{
    using namespace std::views;
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    auto constexpr INF = std::numeric_limits<int>::max();
    int n,m,s;
    std::cin >> n >> m >> s;
    --s;
    using side = std::pair<int,int>;
    auto g = std::vector(n,std::vector<side>{});
    for(auto i : iota(0,m)) {
        int u,v,w;
        std::cin >> u >> v >> w;
        --u,--v;
        g[u].emplace_back(v,w);
    }
    auto que = std::deque<int>{};
    auto dis = std::vector(n,INF);
    dis[s] = 0;
    auto inq = std::vector(n,false);
    inq[s] = true;
    que.emplace_back(s);
    while(not que.empty()) {
        auto it = que.front();
        que.pop_front();
        inq[it] = false;
        for(auto [v,w] : g[it]) {
            if(dis[v] <= dis[it] + w) {
                continue;
            }
            dis[v] = dis[it] + w;
            if(inq[v]) {
                continue;
            }
            inq[v] = true;
            que.empty() or dis[v] > dis[que.front()] ? que.emplace_back(v) : que.emplace_front(v);
        }
    }
    for(auto val : dis) {
        std::cout << val << ' ';
    }

}