

#include<bits/stdc++.h>

using namespace std::views;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,k;
    std::cin >> n >> k;
    auto a = std::vector(n,std::vector<int>{});
    for(int x,y; auto i : iota(1,n)) {
        std::cin >> x >> y;
        --x,--y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    auto d = std::vector(n,0); {
        auto dfs = [&](auto&& self,int it,int fa,int dep) -> void {
            d[it] = dep;
            for(auto i : a[it] | filter([&](auto i){ return i != fa; })) {
                self(self,i,it,dep + 1);
            }
        };
        dfs(dfs,0,0,0);
    }
    auto step = std::invoke([&] {
        auto max = std::ranges::max(d);
        return std::bit_width(static_cast<std::make_unsigned_t<decltype(max)>>(max));
    });
    auto f = std::vector(n,std::vector(step,0)); {
        auto dfs = [&](auto&& self,int it,int fa) -> void {
            f[it][0] = fa;
            for(auto p : iota(1,step)) {
                f[it][p] = f[f[it][p - 1]][p - 1];
            }
            for(auto i : a[it] | filter([&](auto i){ return i != fa; })) {
                self(self,i,it);
            }
        };
        dfs(dfs,0,0);
    }
    auto lca = [&](int x,int y) {
        if(d[x] < d[y]) {
            std::swap(x,y);
        }
        for(auto dd = std::make_unsigned_t<decltype(d[x] - d[y])>(d[x] - d[y]); dd; dd -= dd & -dd) {
            x = f[x][std::countr_zero(dd)];
        }
        // for(auto dd = d[x] - d[y]; auto p : iota(0,step) | filter([&](auto p){ return bool(dd >> p & 1); })) {
        //     x = f[x][p];
        // }
        if(x == y) {
            return x;
        }
        for(auto p : iota(0,step) | reverse | filter([&](auto p){ return f[x][p] != f[y][p]; })) {
            std::tie(x,y) = { f[x][p],f[y][p] };
        }
        return f[x][0];
    };
    auto diff = std::vector(n,0);
    for(int s,t; auto i : iota(0,k)) {
        std::cin >> s >> t;
        --s,--t;
        auto u = lca(s,t),v = f[u][0];
        ++diff[s],++diff[t],--diff[u],--diff[v];
    }
    {
        auto dfs = [&](auto&& self,int it,int fa) -> void {
            for(auto i : a[it] | filter([&](auto i){ return i != fa; })) {
                self(self,i,it);
                diff[it] += diff[i];
            }
        };
        dfs(dfs,0,0);
    }
    std::cout << std::ranges::max(diff);
    std::cout << std::flush;
}