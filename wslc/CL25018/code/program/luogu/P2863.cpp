

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto g = std::vector(n,std::vector<int>{});
    for(auto i = 0; i != m; ++i) {
        int a,b;
        std::cin >> a >> b;
        --a,--b;
        g[a].emplace_back(b);
    }

    auto dfn = std::vector(n,-1),low = dfn;
    auto scc = std::map<int,std::vector<int>>{};
    auto tot = 0;
    auto stk = std::vector<int>{};
    auto vis = std::vector(n,false);
    auto dfs = [&](auto&& dfs,int u) -> void {
        stk.push_back(u);
        vis[u] = true;
        dfn[u] = low[u] = tot++;
        for(auto i = 0; i != g[u].size(); ++i) {
            auto v = g[u][i];
            if(dfn[v] == -1) {
                dfs(dfs,v);
                low[u] = std::min(low[u],low[v]);
            } else if(vis[v]) { // 即使包含收容点 也无所谓 不影响最终结果
                low[u] = std::min(low[u],dfn[v]);
            }
        }
        if(dfn[u] == low[u]) {
            auto& vec = scc[low[u]];
            int v;
            do {
                v = stk.back();
                stk.pop_back();
                vis[v] = false;
                vec.push_back(v);
            } while(u != v);
        }
    };

    for(auto i = 0; i != n; ++i) {
        if(dfn[i] != -1) {
            continue;
        }
        dfs(dfs,i);
    }

    auto cnt = 0;
    for(auto const& [i,vec] : scc) {
        if(vec.size() > 1) {
            ++cnt;
        }
    }
    std::cout << cnt;

}