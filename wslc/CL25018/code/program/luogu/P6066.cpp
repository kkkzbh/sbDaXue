

#include <bits/stdc++.h>

using namespace std::views;

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke([] static noexcept {
        unsigned n,m;
        std::cin >> n >> m;
        auto g = std::vector(n,std::vector<unsigned>{});
        auto deg = std::vector(n,0u);
        for(auto i : iota(0u) | take(m)) {
            unsigned x,y;
            std::cin >> x >> y;
            --x,--y;
            g[x].push_back(y);
            g[y].push_back(x);
            ++deg[x],++deg[y];
        }
        auto path = std::vector<unsigned>{};
        auto map = std::vector(m,0u);
        std::invoke([&](this auto&& dfs,unsigned const i) noexcept -> void {
            for(auto& mi = map[i]; mi < g[i].size(); ) {
                auto const& v = g[i][mi];
                ++mi;
                dfs(v);
            }
            path.push_back(i + 1);
        },0);
        for(auto const& v : path) {
            std::println("{}",v);
        }
    });
}