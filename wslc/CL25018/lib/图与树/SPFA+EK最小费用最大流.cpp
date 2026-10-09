

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m,s,t;
    std::cin >> n >> m >> s >> t;
    --s,--t;
    using node = std::tuple<int,int,int,int>;
    auto g = std::vector(n,std::vector<node>{});
    using namespace std::views;
    for(auto i : iota(0,m)) {
        int u,v,w,c;
        std::cin >> u >> v >> w >> c;
        --u,--v;
        g[u].emplace_back(v,w,c,g[v].size());
        g[v].emplace_back(u,0,-c,g[u].size() - 1);
    }
    auto constexpr INF = std::numeric_limits<int>::max();
    auto pre = std::vector(n,-1);
    auto prev = std::vector(n,-1);
    auto spfa = [&]() {
        auto dis = std::vector(n,INF);
        dis[s] = 0;
        auto que = std::deque<int>{};
        que.push_back(s);
        auto inq = std::vector(n,false);
        inq[s] = true;
        while(not que.empty()) {
            auto it = que.front();
            que.pop_front();
            inq[it] = false;
            for(auto i : iota(0) | take(g[it].size())) {
                auto const& [v,w,c,k] = g[it][i];
                if(w == 0 or dis[it] + c >= dis[v]) {
                    continue;
                }
                dis[v] = dis[it] + c;
                pre[v] = it;
                prev[v] = i;
                if(not inq[v]) {
                    que.empty() or dis[que.front()] ? que.push_back(v) : que.push_front(v);
                    inq[v] = true;
                }
            }
        }
        return dis[t] != INF;
    };
    auto ans1 = 0,ans2 = 0;
    while(spfa()) {
        auto it = t;
        auto flow = INF;
        auto sum = 0;
        while(it != s) {
            auto p = pre[it],pv = prev[it];
            auto const& [v,w,c,k] = g[p][pv];
            flow = std::min(flow,w);
            sum += c;
            it = p;
        }
        it = t;
        while(it != s) {
            auto p = pre[it],pv = prev[it];
            auto& [v,w,c,k] = g[p][pv];
            auto& [v2,w2,c2,k2] = g[v][k];
            w -= flow;
            w2 += flow;
            it = p;
        }
        ans1 += flow;
        ans2 += flow * sum;
    }
    std::cout << ans1 << ' ' << ans2;
}