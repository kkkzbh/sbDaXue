

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,q;
    std::cin >> n >> q;
    using node = std::pair<int,int>;
    auto g = std::vector(n,std::vector<node>{});
    for(auto i = 1; i != n; ++i) {
        int x,y,w;
        std::cin >> x >> y >> w;
        --x,--y;
        g[x].emplace_back(y,w);
        g[y].emplace_back(x,w);
    }
    auto sum = std::vector(n,0);
    auto dp = std::vector(n,std::vector(q + 1,0));
    auto dfs = [&](auto&& dfs,int u,int fa) -> void {
        for(auto const& [v,w] : g[u]) {
            if(v == fa) {
                continue;
            }
            dfs(dfs,v,u);
            sum[u] += sum[v] + 1;
            for(auto j = std::min(sum[u],q); j >= 0; --j) {
                for(auto k = std::min(sum[v],j - 1); k >= 0; --k) {
                    dp[u][j] = std::max(dp[u][j],dp[v][k] + dp[u][j - k - 1] + w);
                }
            }
        }
    };
    dfs(dfs,0,-1);
    std::cout << dp[0][q];

}