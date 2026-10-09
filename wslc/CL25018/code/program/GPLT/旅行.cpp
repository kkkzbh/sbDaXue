

#include <bits/extc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m,q;
    std::cin >> n >> m >> q;
    using side = std::pair<int,int>;
    auto g = std::vector(n,std::vector<side>{});
    auto vg = g;
    for(auto i = 0; i != m; ++i) {
        int u,v,w;
        std::cin >> u >> v >> w;
        --u,--v;
        g[u].emplace_back(v,w);
        vg[v].emplace_back(u,w);
    }
    using namespace __gnu_pbds;
    auto constexpr INF = std::numeric_limits<int>::max() / 2;
    auto vdis = std::vector(n,INF);
    auto proj_fn = [&](int i) {
        return vdis[i];
    };
    auto cmp_fn = std::greater{};
    auto cmp = [=](int x,int y) {
        return cmp_fn(proj_fn(x),proj_fn(y));
    };
    vdis[0] = 0;
    auto que = priority_queue<int,decltype(cmp)>{ cmp };
    auto ique = std::vector(n,decltype(que)::point_iterator{});
    for(auto i = 0; i != n; ++i) {
        ique[i] = que.push(i);
    }
    auto vis = std::vector(n,false);
    auto dijkstra = [&](auto const& g) {
        while(not que.empty()) {
            auto it = que.top();
            que.pop();
            vis[it] = true;
            for(auto [v,w] : g[it]) {
                if(vis[v]) {
                    continue;
                }
                if(vdis[it] + w < vdis[v]) {
                    vdis[v] = vdis[it] + w;
                    que.modify(ique[v],v);
                }
            }
        }
    };
    dijkstra(g);
    auto dis = std::move(vdis);
    vdis.assign(n,INF);
    vdis[n - 1] = 0;
    for(auto i = 0; i != n; ++i) {
        ique[i] = que.push(i);
    }
    std::fill(vis.begin(),vis.end(),false);
    dijkstra(vg);
    auto constexpr ans = std::array{ "no","yes" };
    for(auto i = 0; i != q; ++i) {
        int x;
        std::cin >> x;
        --x;
        std::cout << ans[dis[x] + vdis[x] == dis[n - 1]] << '\n';
    }

}