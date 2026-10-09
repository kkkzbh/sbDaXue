

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    auto r = std::vector(n,0);
    for(auto& val : r) {
        std::cin >> val;
    }
    auto g = std::vector(n,std::vector<int>{});
    auto id = std::vector(n,0);
    for(auto i = 1; i != n; ++i) {
        int l,k;
        std::cin >> l >> k;
        --l,--k;
        g[k].emplace_back(l);
        ++id[l];
    }
    auto dp = std::vector(n,std::array<std::optional<int>,2>{});
    auto dfs = [&](auto&& dfs,int u,bool take) -> void {
        if(dp[u][take]) {
            return;
        }
        if(take) {
            dp[u][take] = r[u];
            for(auto v : g[u]) {
                dfs(dfs,v,false);
                *dp[u][take] += std::max(*dp[v][false],0);
            }
        } else {
            dp[u][take] = 0;
            for(auto v : g[u]) {
                dfs(dfs,v,true),dfs(dfs,v,false);
                *dp[u][take] += std::max({ *dp[v][true],*dp[v][false],0 });
            }
        }
    };
    int root;
    for(auto i = 0; i != n; ++i) {
        if(id[i] == 0) {
            root = i;
            break;
        }
    }
    dfs(dfs,root,true);
    dfs(dfs,root,false);
    std::cout << std::max(*dp[root][true],*dp[root][false]);

}