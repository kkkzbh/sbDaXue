

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    auto r = std::vector(n,0);
    auto g = std::vector(n,std::vector<int>{});
    auto f = std::vector(n,0);
    for(auto i = 0; i != n; ++i) {
        auto u = i;
        int y;
        std::cin >> r[u] >> y;
        --y;
        g[y].emplace_back(u);
        f[u] = y;
    }
    using i64 = long long;
    auto dp = std::vector(n,std::array<i64,2>{});
    auto vis = std::vector(n,false);
    auto find = [&](auto&& find,int u) -> int {
        vis[u] = true;
        if(vis[f[u]]) {
            return f[u];
        }
        return find(find,f[u]);
    };
    auto ans = 0LL;
    for(auto i = 0; i != n; ++i) {
        if(vis[i]) {
            continue;
        }
        auto root = find(find,i);
        auto dfs = [&](auto&& dfs,int u) -> void {
            dp[u][1] = r[u];
            dp[u][0] = 0LL;
            vis[u] = true;
            for(auto v : g[u]) {
                if(v == root) {
                    continue;
                }
                dfs(dfs,v);
                dp[u][1] += dp[v][0];
                dp[u][0] += std::max(dp[v][1],dp[v][0]);
            }
        };
        dfs(dfs,root);
        auto val = dp[root][0];
        root = f[root];
        dfs(dfs,root);
        ans += std::max(val,dp[root][0]);
    }
    std::cout << ans;

}