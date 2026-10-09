

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
            if(x == y) {
                continue;
            }
            g[x].emplace_back(y);
            g[y].emplace_back(x);
        }
        auto dfn = std::vector(n,0u);
        auto low = std::vector(n,0u);
        auto tot = 0u;
        auto edge = empty<std::pair<unsigned,unsigned>> | std::ranges::to<std::set>([](auto const& p1,auto const& p2) static noexcept {
            auto const& [x1,y1] = p1;
            auto const& [x2,y2] = p2;
            return std::minmax(x1,y1) < std::minmax(x2,y2);
        });
        for(auto first = 0u; first != n; ++first) {
            if(low[first]) {
                continue;
            }
            std::invoke([&](this auto&& dfs,unsigned const i,unsigned const fa) noexcept -> void {
                dfn[i] = low[i] = ++tot;
                auto ok = false;
                for(auto const v : g[i]) {
                    if(not ok and v == fa) {
                        ok = true;
                        continue;
                    }
                    if(not low[v]) {
                        dfs(v,i);
                        low[i] = std::min(low[i],low[v]);
                        if(low[v] > dfn[i]) {
                            edge.emplace(i,v);
                        }
                    } else {
                        low[i] = std::min(low[i],dfn[v]);
                    }
                }
            },first,first);
        }
        auto vis = std::vector(n,false);
        auto ans = std::vector<std::vector<unsigned>>{};
        for(auto first = 0u; first != n; ++first) {
            if(vis[first]) {
                continue;
            }
            ans.emplace_back();
            std::invoke([&,&path = ans.back()](this auto&& dfs,unsigned const i) noexcept -> void {
                vis[i] = true;
                path.emplace_back(i);
                for(auto const v : g[i] | filter([&](auto const v) noexcept {
                    using side = decltype(edge)::value_type;
                    return not vis[v] and not edge.contains(side{ i,v });
                })) {
                    dfs(v);
                }
            },first);
        }
        std::cout << ans.size() << '\n';
        for(auto const& vec : ans) {
            std::cout << vec.size() << ' ';
            for(auto const& val : vec) {
                std::cout << val + 1 << ' ';
            }
            std::println(std::cout);
        }

    });
}
