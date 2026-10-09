

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m,q;
    std::cin >> n >> m >> q;
    using i64 = long long;
    auto constexpr INF = std::numeric_limits<i64>::max() / 2;
    auto a = std::vector(n,std::vector(n,INF));
    for(auto i = 0; i != n; ++i) {
        a[i][i] = 0;
    }
    for(auto i = 0; i != m; ++i) {
        int u,v,w;
        std::cin >> u >> v >> w;
        --u,--v;
        a[u][v] = a[v][u] = std::min<i64>(a[u][v],w);
    }
    for(auto k = 0; k != n; ++k) {
        for(auto i = 0; i != n; ++i) {
            for(auto j = 0; j != n; ++j) {
                a[i][j] = std::min(a[i][j],a[i][k] + a[k][j]);
            }
        }
    }
    for(auto i = 0; i != q; ++i) {
        int s,t;
        std::cin >> s >> t;
        if(a[s][t] == INF) {
            std::cout << "-1\n";
            continue;
        }
        std::cout << a[s][t] << '\n';
    }

}