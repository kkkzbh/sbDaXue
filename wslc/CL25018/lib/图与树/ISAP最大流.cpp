

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m,s,t;
    std::cin >> n >> m >> s >> t;
    --s,--t;
    auto g = std::vector(n,std::map<int,int64_t>{});
    using namespace std::views;
    for(auto i : iota(0,m)) {
        int u,v,w;
        std::cin >> u >> v >> w;
        --u,--v;
        g[u][v] += w;
        g[v][u];
    }
    auto ans = [&]() {
        auto h = std::vector(n,n); // 深度
        auto gap = std::vector(n + 1,0);
        auto que = std::deque<int>{};
        que.push_back(t);
        h[t] = 0;
        while(not que.empty()) {
            auto it = que.front();
            que.pop_front();
            ++gap[h[it]];
            for(auto const& [v,w] : g[it]) {
                if(g[v][it] and h[v] == n) {
                    h[v] = h[it] + 1;
                    que.push_back(v);
                }
            }
        }
        auto flow = 0LL;
        auto it = s;
        auto now = std::vector(n,decltype(g)::value_type::iterator{});
        for(auto i : iota(0,n)) {
            now[i] = g[i].begin();
        }
        auto pre = std::vector(n,-1);
        auto constexpr INF = std::numeric_limits<int64_t>::max() / 2;
        auto solve = [&]() {
            auto it = t;
            auto flow = INF;
            while(it != s) {
                flow = std::min(flow,g[pre[it]][it]);
                it = pre[it];
            }
            it = t;
            while(it != s) {
                auto prev = pre[it];
                g[prev][it] -= flow;
                g[it][prev] += flow;
                it = prev;
            }
            return flow;
        };
        auto tot = 0;
        while(h[s] != n) {
            if(it == t) {
                flow += solve();
                it = s;
            }
            ++tot;
            auto ok = false;
            for(auto& i = now[it]; i != g[it].end(); ++i) {
                auto const& [v,w] = *i;
                if(g[it][v] and h[v] + 1 == h[it]) {
                    ok = true;
                    pre[v] = it;
                    it = v;
                    break;
                }
            }
            if(not ok) {
                if(not --gap[h[it]]) {
                    break;
                }
                auto r = g[it] | filter([&](auto const& nd) {
                    auto const& [v,w] = nd;
                    return w;
                }) | keys | transform([&](auto v){ return h[v]; });
                h[it] = r.empty() ? n : std::ranges::min(r) + 1;
                ++gap[h[it]];
                now[it] = g[it].begin();
                if(it != s) {
                    it = pre[it];
                }
            }
        }
        return flow;
    }();
    std::cout << ans;

}