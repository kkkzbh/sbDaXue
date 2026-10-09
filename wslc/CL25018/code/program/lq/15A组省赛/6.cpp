

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    unsigned n,q;
    std::cin >> n >> q;
    auto a = std::vector(n,0);
    for(auto& v : a) {
        std::cin >> v;
        --v;
    }
    auto g = std::vector(n,std::vector<int>{});
    for(auto i = 1; i != n; ++i) {
        int u,v;
        std::cin >> u >> v;
        --u,--v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    auto pb = 32 - __builtin_clz(n);
    auto root = 0;
    auto fa = std::vector(n,std::vector(pb,0));
    auto presum = std::vector(n,std::valarray(0,20));
    auto dep = std::vector(n,0);
    auto dfs = [&](auto&& dfs,int it) -> void {
        auto father = fa[it][0];
        presum[it] = presum[father];
        ++presum[it][a[it]];
        dep[it] = dep[father] + 1;
        for(auto p = 1; p != pb; ++p) {
            fa[it][p] = fa[fa[it][p - 1]][p - 1];
        }
        for(auto v : g[it]) {
            if(v == father) {
                continue;
            }
            fa[v][0] = it;
            dfs(dfs,v);
        }
    };
    dep[root] = -1;
    dfs(dfs,root);
    auto lca = [&](int x,int y) -> int {
        if(dep[x] < dep[y]) {
            std::swap(x,y);
        }
        for(auto p = pb; p--; ) {
            if(dep[fa[x][p]] < dep[y]) {
                continue;
            }
            x = fa[x][p];
        }
        if(x == y) {
            return x;
        }
        for(auto p = pb; p--; ) {
            auto nx = fa[x][p],ny = fa[y][p];
            if(nx == ny) {
                continue;
            }
            std::tie(x,y) = { nx,ny };
        }
        return fa[x][0];
    };
    for(auto i = 0; i != q; ++i) {
        int s,t;
        std::cin >> s >> t;
        --s,--t;
        auto f = lca(s,t);
        auto pres = presum[s];
        auto pret = presum[t];
        auto pref = presum[f];
        pres -= pref;
        pret -= pref;
        ++pres[a[f]];
        auto cans = 0;
        for(auto i = 0; i != 20; ++i) {
            if(pres[i] or pret[i]) {
                ++cans;
            }
        }
        std::cout << cans << '\n';
    }


}