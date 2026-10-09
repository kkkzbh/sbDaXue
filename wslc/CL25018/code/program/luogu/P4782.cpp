

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto g = std::vector(n * 2,std::vector<int>{});
    for(auto i = 0; i != m; ++i) {
        int x,a,y,b;
        std::cin >> x >> a >> y >> b;
        --x,--y;
        auto va = a ^ 1,vb = b ^ 1;
        g[x + va * n].emplace_back(y + b * n);
        g[y + vb * n].emplace_back(x + a * n);
    }
    auto scc = std::vector(n * 2,-1);
    auto tot = 0;
    auto dfn = std::vector(n * 2,-1),low = dfn;
    auto stk = std::vector<int>{};
    auto cnt = 0;
    auto dfs = [&](auto&& dfs,int u) -> void {
        stk.emplace_back(u);
        dfn[u] = low[u] = tot++;
        for(auto v : g[u]) {
            if(dfn[v] == -1) {
                dfs(dfs,v);
                low[u] = std::min(low[u],low[v]);
            } else if(scc[v] == -1) {
                low[u] = std::min(low[u],dfn[v]);
            }
        }
        if(dfn[u] == low[u]) {
            int v;
            do {
                v = stk.back();
                scc[v] = cnt;
                stk.pop_back();
            } while(v != u);
            ++cnt;
        }
    };
    for(auto i = 0,bound = n * 2; i != bound; ++i) {
        if(dfn[i] != -1) {
            continue;
        }
        dfs(dfs,i);
    }
    for(auto i = 0; i != n;++i) {
        if(scc[i] == scc[i + n]) {
            std::cout << "IMPOSSIBLE";
            return 0;
        }
    }
    std::cout << "POSSIBLE" << '\n';
    for(auto i = 0; i != n; ++i) {
        std::cout << int(scc[i] > scc[i + n]) << ' ';
    }

}
