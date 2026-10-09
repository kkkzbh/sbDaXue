

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m,e;
    std::cin >> n >> m >> e;
    auto g = std::vector(n,std::vector(m,0));
    using namespace std::views;
    for(auto i : iota(0,e)) {
        int u,v;
        std::cin >> u >> v;
        --u,--v;
        g[u][v] = 1;
    }
    auto vis = std::vector(m,0);
    auto match = std::vector(m,-1);
    auto dfs = [&](auto&& self,int it) -> bool {
        for(auto i : iota(0,m)) {
            if(not vis[i] and g[it][i]) {
                vis[i] = 1;
                if(match[i] == -1 or self(self,match[i])) {
                    match[i] = it;
                    return true;
                }
            }
        }
        return false;
    };
    auto ans = 0;
    for(auto i : iota(0,n)) {
        ans += dfs(dfs,i);
        std::ranges::fill(vis,0);
    }
    std::cout << ans;

}












