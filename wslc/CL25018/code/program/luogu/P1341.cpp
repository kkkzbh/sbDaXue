

#include <bits/stdc++.h>

using namespace std::views;
using namespace std::string_literals;
using namespace std::string_view_literals;
using namespace std::placeholders;

auto constexpr no = "No Solution"sv;

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke([] static noexcept {
        unsigned n;
        std::cin >> n;
        auto mi = std::map<char,unsigned>{};
        auto mc = ""s;
        auto m = 0;
        auto make = [&](char c) noexcept {
            auto [it,ok] = mi.try_emplace(c,m);
            if(ok) {
                mc.push_back(c);
                ++m;
            }
            return std::get<1>(*it);
        };
        auto a = std::vector(0uz,std::make_pair(0u,0u));
        for(auto i : iota(0u) | take(n)) {
            char x,y;
            std::cin >> x >> y;
            a.emplace_back(make(x),make(y));
        }
        auto g = std::vector(m,std::vector(0uz,0u));
        auto G = std::vector(m,std::vector(m,0u));
        auto deg = std::vector(m,0u);
        for(auto const& [x,y] : a) {
            g[x].push_back(y);
            g[y].push_back(x);
            ++deg[x],++deg[y];
            ++G[x][y],++G[y][x];
        }
        auto const cnt = std::ranges::count_if(deg,[](auto const& val) static noexcept { return val & 1; });
        if (
            cnt and cnt != 2 or
            std::invoke([&,vis = std::vector(m,false),n = 0](this auto&& dfs,unsigned const i) noexcept -> bool {
                if(n == m) {
                    return true;
                }
                vis[i] = true;
                ++n;
                return std::ranges::any_of(g[i] | filter([&](auto const& v) noexcept {
                    return not vis[v];
                }),[&](auto const& v) noexcept {
                    return dfs(v);
                });
            },0)
        ) {
            std::println(no);
            return;
        }
        auto first {
            cnt ?
            std::ranges::min (
                iota(0u) | take(m) | filter([&](auto i) noexcept {
                    return deg[i] & 1;
                }),
                {},
                [&](auto i) noexcept {
                    return mc[i];
                }
            ) :
            std::ranges::min (
                iota(0u) | take(m),
                {},
                [&](auto i) noexcept {
                    return mc[i];
                }
            )
        };
        for(auto& vec : g) {
            std::ranges::sort(vec,{},[&](auto i) noexcept {
                return mc[i];
            });
        }
        auto path = std::vector(0uz,0u);
        auto map = std::vector(m,0u);
        std::invoke([&](this auto&& dfs,unsigned const i) noexcept -> void {
            for(auto& cur = map[i]; cur < g[i].size();) {
                auto const& v = g[i][cur++];
                if(not G[i][v]) {
                    continue;
                }
                --G[i][v],--G[v][i];
                dfs(v);
            }
            path.push_back(i);
        },first);
        for(auto const& v : path | reverse) {
            std::print("{}",mc[v]);
        }
    });
}