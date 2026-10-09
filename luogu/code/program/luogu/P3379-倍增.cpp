

#include<bits/stdc++.h>

using namespace std::views;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m,s;
    std::cin >> n >> m >> s;
    --s;
    auto a = std::vector(n,std::vector<int>{});
    for(auto i : iota(1,n)) {
        int x,y;
        std::cin >> x >> y;
        --x,--y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    auto d = std::vector(n,0);
    {
        auto dfs = [&](auto&& self,int it,int fa,int dep) -> void {
            d[it] = dep;
            for(auto i : a[it] | filter([&](auto i){ return i != fa; })) {
                self(self,i,it,dep + 1);
            }
        };
        dfs(dfs,s,s,0);
    }
    auto md = std::ranges::max(d);
    auto step = std::bit_width(static_cast<std::make_unsigned_t<decltype(md)>>(md));
    auto f = std::vector(n,std::vector(step,-1));
    {
        auto dfs = [&](auto&& self,int it,int fa) -> void {
            f[it][0] = fa;
            for(auto p : iota(1,step)) {
                f[it][p] = f[f[it][p - 1]][p - 1];
            }
            for(auto i : a[it] | filter([&](auto i){ return i != fa; })) {
                self(self,i,it);
            }
        };
        dfs(dfs,s,s);
    }
    auto lca = [&](int x,int y) {
        if(d[x] != d[y]) {
            std::tie(x,y) = std::make_pair(std::ranges::min(x,y,{},[&](auto i){ return d[i]; }),std::ranges::max(x,y,{},[&](auto i){ return d[i]; }));
        }
        auto delta = d[y] - d[x];
        for(auto p : iota(0,step) | filter([&](auto p){ return static_cast<bool>(delta >> p & 1); })) {
            y = f[y][p];
        }
        if(x == y) {
            return x;
        }
        for(auto p : iota(0,step) | reverse | filter([&](auto p){ return f[x][p] != f[y][p]; })) {
            std::tie(x,y) = { f[x][p],f[y][p] };
        }
        return f[x][0];
    };
    for(auto i : iota(0,m)) {
        int a,b;
        std::cin >> a >> b;
        --a,--b;
        std::cout << lca(a,b) + 1 << '\n';
    }
    std::cout << std::flush;

}