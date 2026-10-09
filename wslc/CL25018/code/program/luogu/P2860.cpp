

#include <bits/stdc++.h>

using namespace std::views;
using uint = std::uint32_t;

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    [] static noexcept {
        uint n,m;
        std::cin >> n >> m;

        auto g = std::vector(n,std::vector<std::pair<uint,uint>>{});
        auto tot = 0u;
        for(auto i : iota(0u) | take(m)) {
            uint x,y;
            std::cin >> x >> y;
            --x,--y;
            g[x].emplace_back(y,tot++);
            g[y].emplace_back(x,tot++);
        }

        auto dfn = std::vector(n,0u);
        auto low = std::vector(n,0u);
        auto edge = std::vector(std::exchange(tot,0u),false);
        for(auto first = 0u; first != n; ++first) {
            if(dfn[first]) {
                continue;
            }
            [&](this auto&& dfs,uint const i,uint const fv) noexcept -> void {
                dfn[i] = low[i] = ++tot;
                for(auto const& [v,si] : g[i] | filter([&](auto const& p) noexcept { return (std::get<1>(p) ^ fv) != 1u; })) {
                    if(not dfn[v]) {
                        dfs(v,si);
                        low[i] = std::min(low[i],low[v]);
                        if(low[v] > dfn[i]) {
                            edge[si] = edge[si ^ 1u] =  true;
                        }
                    } else {
                        low[i] = std::min(low[i],dfn[v]);
                    }
                }
            }(first,-1u);
        }
        auto constexpr null = -1u;
        dfn.assign(n,null);
        tot = 0u;
        for(auto first = 0u; first != n; ++first) {
            if(dfn[first] != null) {
                continue;
            }
            [&](this auto&& dfs,uint const i) noexcept -> void {
                dfn[i] = tot;
                for(auto const& [v,_] : g[i] | filter([&](auto const& p) noexcept {
                    auto const& [v,si] = p;
                    return dfn[v] == null and not edge[si];
                })) {
                    dfs(v);
                }
            }(first);
            ++tot;
        }

        auto deg = std::vector(tot,0u);
        for(auto const i : iota(0u,n)) {
            for(auto const& v : g[i] | keys | filter([&](auto const& v) noexcept {
                return dfn[i] != dfn[v];
            })) {
                ++deg[dfn[i]];
            }
        }

        auto const ans = (std::ranges::count_if(deg,[](auto const& val) static noexcept {
            return val == 1;
        }) + 1) / 2;

        std::cout << ans;

    }();

}