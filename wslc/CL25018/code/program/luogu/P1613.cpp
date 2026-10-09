

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto constexpr ln = sizeof(long) * 8;
    auto dp = std::vector(n,std::vector(m,std::vector(ln + 1,false)));
    auto constexpr INF = std::numeric_limits<long>::max() / 2;
    auto g = std::vector(n,std::vector(m,INF));
    for(auto i = 0; i != m; ++i) {
        int u,v;
        std::cin >> u >> v;
        --u,--v;
        dp[u][v][0] = true;
        g[u][v] = 1;
    }
    for(auto p = 1; p <= ln; ++p) {
        for(auto k = 0; k != n; ++k) {
            for(auto i = 0; i != n; ++i) {
                for(auto j = 0; j != n; ++j) {
                    if(dp[i][k][p - 1] and dp[k][j][p - 1]) {
                        dp[i][j][p] = true;
                        g[i][j] = 1;
                    }
                }
            }
        }
    }
    for(auto k = 0; k != n; ++k) {
        for(auto i = 0; i != n; ++i) {
            for(auto j = 0; j != n; ++j) {
                g[i][j] = std::min(g[i][j],g[i][k] + g[k][j]);
            }
        }
    }
    std::cout << g[0][n - 1];

}