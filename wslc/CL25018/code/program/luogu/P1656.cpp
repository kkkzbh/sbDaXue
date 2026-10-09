

#include <bits/stdc++.h>

using namespace std::views;

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke([] static noexcept {
        unsigned n,m;
        std::cin >> n >> m;
        auto g = std::vector(n,std::vector<unsigned>{});
        for(auto i : iota(0u) | take(m)) {
            unsigned x,y;
            std::cin >> x >> y;
            --x,--y;
            g[x].emplace_back(y);
            g[y].emplace_back(x);
        }
        auto dfn = std::vector(n,0u);
        auto ans = std::vector<std::pair<unsigned,unsigned>>{};
        auto low = std::vector(n,0u);
        auto tot = 0u;
        for(auto root = 0u; root != n; ++root) {
            if(dfn[root]) {
                continue;
            }
            std::invoke([&](this auto&& dfs,unsigned const i,unsigned const fa) noexcept -> void {
                dfn[i] = low[i] = ++tot;
                auto ct = 0u;
                auto ok = false;
                for(auto const& v : g[i]) {
                    if(not ok and v == fa) {
                        ok = true;
                        continue;
                    }
                    if(not dfn[v]) {
                        ++ct;
                        dfs(v,i);
                        low[i] = std::min(low[i],low[v]);
                        if(low[v] > dfn[i]) {
                            ans.emplace_back(i + 1u,v + 1u);
                        }
                    } else { // 回边 -> 排除树边和横边 和下边 (下横边已经被计算消除)
                        low[i] = std::min(low[i],dfn[v]);
                    }
                }
            },root,root);
        }
        std::ranges::sort(ans);
        for(auto const& [x,y] : ans) {
            std::println("{} {}",x,y);
        }
    });
}