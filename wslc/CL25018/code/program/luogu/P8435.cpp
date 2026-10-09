

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
        auto que = empty<unsigned> | std::ranges::to<std::deque>();
        auto ans = std::vector<std::flat_set<unsigned>>{};
        auto r = std::vector<unsigned>{};
        for(auto root = 0u; root != n; ++root) {
            if(dfn[root]) {
                continue;
            }
            if(g[root].empty()) { // 独立节点
                ans.emplace_back(single(root) | std::ranges::to<std::flat_set>());
                continue;
            }
            std::invoke([&](this auto&& dfs,unsigned const i,unsigned const fa) noexcept -> void {
                dfn[i] = low[i] = ++tot;
                auto ct = 0u;
                que.emplace_back(i);
                for(auto const& v : g[i]) {
                    if(not dfn[v]) {
                        ++ct;
                        dfs(v,i);
                        low[i] = std::min(low[i],low[v]);
                        if(low[v] >= dfn[i] and (i != root or ct > 1)) {
                            do {
                                auto const x = que.back();
                                r.emplace_back(x);
                            } while(que.back() != v and (que.pop_back(),true));
                            que.pop_back();
                            r.emplace_back(i);
                            ans.emplace_back(std::move(r) | std::ranges::to<std::flat_set>());
                            r.clear();
                        }
                    } else if(dfn[v] < dfn[i] and v != fa) { // 回边
                        low[i] = std::min(low[i],dfn[v]);
                    }
                }
            },root,root);
                if(not que.empty()) {
                    while(not que.empty()) {
                        auto const x = que.back();
                        que.pop_back();
                        r.emplace_back(x);
                    }
                    ans.emplace_back(std::move(r) | std::ranges::to<std::flat_set>());
                    r.clear();
                }
        }
        std::println("{}",ans.size());
        for(auto const& set : ans) {
            std::print("{} ",set.size());
            for(auto const& val : set) {
                std::print("{} ",val + 1);
            }
            std::println();
        }
    });
}