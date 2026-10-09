

#include <bits/extc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    using side = std::pair<int,int>;
    auto g = std::vector(n,std::vector<side>{});
    auto vg = g;
    for(auto i = 0; i != m; ++i) {
        int u,v,w;
        std::cin >> u >> v >> w;
        g[--u].emplace_back(--v,w);
        vg[v].emplace_back(u,w);
    }
    auto constexpr INF = std::numeric_limits<int>::max();
    auto dis = std::vector(n,INF);
    using namespace __gnu_pbds;
    auto cmp_fn = std::greater{};
    auto proj = [&](int i) { return dis[i]; };
    auto cmp = [=](int x,int y) { return cmp_fn(proj(x),proj(y)); };
    auto que = priority_queue<int,decltype(cmp)>{ cmp };
    auto iq = std::vector(n,decltype(que)::point_iterator{});
    dis[0] = 0;
    for(auto i = 0; i != n; ++i) {
        iq[i] = que.push(i);
    }
    while(not que.empty() and dis[que.top()] != INF) {
        auto it = que.top();
        que.pop();
        for(auto [v,w] : g[it]) {
            if(dis[it] + w >= dis[v]) {
                continue;
            }
            dis[v] = dis[it] + w;
            que.modify(iq[v],v);
        }
    }
    auto dis2 = std::move(dis);
    dis.assign(n,INF);
    dis[0] = 0;
    for(auto i = 0; i != n; ++i) {
        iq[i] = que.push(i);
    }
    while(not que.empty() and dis[que.top()] != INF) {
        auto it = que.top();
        que.pop();
        for(auto [v,w] : vg[it]) {
            if(dis[it] + w >= dis[v]) {
                continue;
            }
            dis[v] = dis[it] + w;
            que.modify(iq[v],v);
        }
    }

    auto ans = 0LL;
    for(auto i = 1; i != n; ++i) {
        ans += dis[i];
        ans += dis2[i];
    }
    std::cout << ans;


}