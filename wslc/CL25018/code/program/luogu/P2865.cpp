

#include <bits/extc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    unsigned n,m,a,b;
    std::cin >> n >> m;
    using energy = unsigned;
    energy k;
    k = 2;
    a = 0,b = n - 1;
    using node = std::pair<unsigned,energy>;
    auto g = std::vector(n,std::vector<node>{});
    using namespace std::views;
    for(auto i : iota(0u,m)) {
        unsigned u,v;
        energy l;
        std::cin >> u >> v >> l;
        --u,--v;
        g[u].emplace_back(v,l);
        g[v].emplace_back(u,l);
    }
    auto wd = [&]() {
        using namespace __gnu_pbds;
        auto cmp_fn = std::greater{};
        auto constexpr INF = std::numeric_limits<energy>::max() / 2;
        auto dis = std::vector(n,INF);
        auto proj = [&](auto i){ return dis[i]; };
        auto cmp = [=](auto lhs,auto rhs){ return cmp_fn(proj(lhs),proj(rhs)); };
        auto que = priority_queue<unsigned,decltype(cmp)>{ cmp };
        dis[b] = 0;
        auto iq = std::vector(n,decltype(que)::point_iterator{});
        for(auto i : iota(0u,n)) {
            iq[i] = que.push(i);
        }
        while(not que.empty()) {
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
        return dis;
    }();
    using qnd = std::pair<unsigned,energy>;
    auto cmp_fn = std::greater{};
    auto proj = [&](qnd const& nd) {
        auto const& [i,distance] = nd;
        return distance + wd[i];
    };
    auto cmp = [=](qnd const& lhs,qnd const& rhs){ return cmp_fn(proj(lhs),proj(rhs)); };
    auto que = std::priority_queue<qnd,std::vector<qnd>,decltype(cmp)>{ cmp };
    que.emplace(a,0u);
    auto ans = std::optional<unsigned>{};
    while(not que.empty()) {
        auto [it,dis] = que.top();
        que.pop();
        if(it == b) {
            if(ans) {
                if(dis > ans) {
                    *ans = dis;
                    goto aans;
                }
            } else {
                ans = dis;
            }
        }
        for(auto [v,w] : g[it]) {
            que.emplace(v,dis + w);
        }
    }

    aans:
    std::cout << *ans;

}