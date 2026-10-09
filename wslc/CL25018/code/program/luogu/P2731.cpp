

#include <bits/stdc++.h>

using namespace std::views;

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke([] static noexcept {
        unsigned m;
        std::cin >> m;
        auto static g = std::array<std::vector<unsigned>,500uz>{};
        auto static gg = std::array<std::array<unsigned,500uz>,500uz>{};
        auto static deg = std::array<unsigned,500uz>{};
        for(auto i : iota(0u) | take(m)) {
            unsigned x,y;
            std::cin >> x >> y;
            --x,--y;
            g[x].push_back(y);
            g[y].push_back(x);
            ++deg[x],++deg[y];
            ++gg[x][y],++gg[y][x];
        }
        std::ranges::for_each(g,std::ranges::sort);
        auto odd = [](auto const& val) static noexcept {
            return val & 1;
        };
        auto const cnt = std::ranges::count_if(deg,odd);
        auto const first = cnt ?
            std::ranges::min(iota(0u) | take(500u) | filter([&](auto const& i) noexcept { return odd(deg[i]); })) :
            static_cast<unsigned>(std::ranges::distance(deg.begin(),std::ranges::find_if(deg,std::identity{})));
        auto path = std::vector(0uz,0u);
        auto map = std::unordered_map<unsigned,unsigned>{};
        std::invoke([&](this auto&& dfs,unsigned const i) noexcept -> void { // NOLINT
            for(auto& mi = map[i]; mi < g[i].size(); ) {
                auto const& v = g[i][mi++];
                if(not gg[i][v] or not gg[v][i]) {
                    continue;
                }
                --gg[i][v],--gg[v][i];
                dfs(v);
             }
            path.push_back(i + 1);
        },first);
        for(auto const& val : path | reverse) {
            std::println("{}",val);
        }

    });
}