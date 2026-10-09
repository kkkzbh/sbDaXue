

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
            g[x].push_back(y);
            g[y].push_back(x);
        }
        auto dfn = std::vector(n,0u);
        auto low = std::vector(n,0u);
        auto tot = 0u;
        auto cup = std::set<unsigned>{};
        auto vis = std::vector(n,false);
        for(auto root = 0u; root != n; ++root) {
            if(vis[root]) {
                continue;
            }
            std::invoke([&](this auto&& dfs,unsigned const i) noexcept -> void {
                dfn[i] = low[i] = tot++;
                vis[i] = true;
                auto ct = 0;
                for(auto const& v : g[i]) {
                    if(not vis[v]) {
                        dfs(v),++ct;
                        low[i] = std::min(low[i],low[v]);
                        if(i != root and low[v] >= dfn[i]) {
                            cup.emplace(i + 1);
                        }
                    } else {
                        low[i] = std::min(low[i],dfn[v]);
                    }
                }
                if(i == root and ct > 1) [[unlikely]] {
                    cup.emplace(i + 1);
                }
            },root);
        }
        std::ranges::sort(cup);
        std::println("{}",cup.size());
        for(auto const& val : cup) {
            std::print("{} ",val);
        }
    });
}