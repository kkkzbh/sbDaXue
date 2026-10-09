

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    uint n,m;
    scan(n,m);
    auto a = std::vector(n,0u);
    scan(a);
    auto g = std::vector(n,std::vector<uint>{});
    for(auto const i : iota(0u,m)) {
        uint u,v;
        scan(u,v);
        --u,--v;
        g[u].emplace_back(v);
    }
    auto dfn = std::vector(n,0u);
    auto low = std::vector(n,0u);
    auto tot = 0u;
    auto scci = std::vector(n,0u);
    auto scc = std::vector<uint>{};
    auto vis = std::vector(n,false);
    auto stk = std::stack<uint>{};
    auto s = std::unordered_map<uint,uint>{};
    auto set = std::set<std::pair<uint,uint>>{};
    auto sg = std::unordered_map<uint,std::vector<uint>>{};
    auto ind = std::unordered_map<uint,uint>{};
    auto dfs = [&](auto&& self,auto const i) -> void {
        dfn[i] = low[i] = ++tot;
        stk.emplace(i);
        for(auto const v : g[i]) {
            if(not vis[v]) {
                vis[v] = true;
                self(self,v);
                low[i] = std::min(low[i],low[v]);
            } else if(not scci[v]) {
                low[i] = std::min(low[i],dfn[v]);
            }
        }
        if(dfn[i] == low[i]) {
            scc.emplace_back(dfn[i]);
            uint v;
            do {
                v = stk.top();
                stk.pop();
                s[dfn[i]] += a[v];
                scci[v] = dfn[i];
                ind[dfn[i]];
                for(auto const to : g[v]) {
                    if(not scci[to] or scci[to] == dfn[i] or set.contains({ dfn[i],scci[to] })) {
                        continue;
                    }
                    set.emplace(dfn[i],scci[to]);
                    sg[dfn[i]].emplace_back(scci[to]);
                    ++ind[scci[to]];
                }
            } while(v != i);
        }
    };

    for(auto i : iota(0u,n)) {
        if(vis[i]) {
            continue;
        }
        vis[i] = true;
        dfs(dfs,i);
    }

    auto que = std::queue<uint>{};
    auto dp = std::unordered_map<uint,uint>{};
    for(auto const [v,id] : ind) {
        if(id) {
           continue;
        }
        que.emplace(v);
        dp[v] = s[v];
    }
    while(not que.empty()) {
        auto const it = que.front();
        que.pop();
        for(auto const v : sg[it]) {
            dp[v] = std::max(dp[v],dp[it] + s[v]);
            if(not --ind[v]) {
                que.emplace(v);
            }
        }
    }
    println("{}",std::ranges::max(dp | values));

}
