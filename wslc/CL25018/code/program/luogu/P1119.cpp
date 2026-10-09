

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto a = std::vector(n,0);
    for(auto& v : a) {
        std::cin >> v;
    }
    auto constexpr INF = std::numeric_limits<int>::max() / 2;
    auto dp = std::vector(n,std::vector(n,INF));
    using side = std::pair<int,int>;
    auto g = std::vector(n,std::vector<side>{});
    for(auto i = 0; i != m; ++i) {
        int u,v,w;
        std::cin >> u >> v >> w;
        g[u].emplace_back(v,w);
        g[v].emplace_back(u,w);
        dp[v][u] = dp[u][v] = w;
    }
    int q;
    std::cin >> q;
    using node = std::tuple<int,int,int>;
    auto qq = std::vector(q,node{});
    for(auto& [x,y,t] : qq) {
        std::cin >> x >> y >> t;
    }
    auto pqq = std::vector(q,0);
    for(auto i = 0; i != q; ++i) {
        pqq[i] = i;
    }
    auto cmp_fn = std::less{};
    auto proj = [&](int i) { return std::get<2>(qq[i]); };
    auto cmp = [=](int lhs,int rhs) { return cmp_fn(proj(lhs),proj(rhs)); };
    std::sort(pqq.begin(),pqq.end(),cmp);
    auto tot = 0;
    auto first = a[0];
    auto ans = std::vector(q,0);
    for(auto k = 0; k != n; ++k) {
        auto bound = a[k];
        while(proj(pqq[tot]) < bound) {
            auto const& [x,y,_] = qq[pqq[tot]];
            if(dp[x][y] == INF or x >= k or y >= k) {
                ans[pqq[tot]] = -1;
            } else {
                ans[pqq[tot]] = dp[x][y];
            }
            if(++tot == q) {
                goto print;
            }
        }
        for(auto const& [v,w] : g[k]) {
            if(v > k) {
                continue;
            }
            dp[k][v] = dp[v][k] = std::min(dp[k][v],w);
        }
        dp[k][k] = 0;
        for(auto i = 0; i != n; ++i) {
            for(auto j = 0; j != n; ++j) {
                dp[i][j] = std::min(dp[i][j],dp[i][k] + dp[k][j]);
            }
        }
    }

    while(tot != q) {
        auto const& [x,y,_] = qq[pqq[tot]];
        if(dp[x][y] == INF) {
            ans[pqq[tot]] = -1;
        } else {
            ans[pqq[tot]] = dp[x][y];
        }
        ++tot;
    }

    print:

    for(auto v : ans) {
        std::cout << v << '\n';
    }

}