

#include<bits/stdc++.h>

using namespace std::views;

struct disjoint_set
{

    explicit disjoint_set(std::integral auto n) : a(n,-1) {}

    auto find(int it) -> int
    {
        if(a[it] < 0) {
            return it;
        }
        return a[it] = find(a[it]);
    }

    auto merge(int x,int y) -> void
    {
        auto fx = find(x),fy = find(y);
        if(fx == fy) {
            return;
        }
        a[fx] = fy;
    }

    auto same(int x,int y) -> bool
    { return find(x) == find(y); }

    std::vector<int> a;
};

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto es = std::vector(m,std::array<int,3>{});
    for(auto& [x,y,z] : es) {
        std::cin >> x >> y >> z;
        --x,--y;
    }
    std::ranges::sort(es,std::greater{},[](auto const& arr){ return std::get<2>(arr); });
    auto a = std::vector(n,std::vector<std::pair<int,int>>{});
    auto set = disjoint_set{ n };
    for(auto const& [x,y,z] : es | filter([&](auto const& arr){ return not set.same(std::get<0>(arr),std::get<1>(arr)); })) {
        set.merge(x,y);
        a[x].emplace_back(y,z);
        a[y].emplace_back(x,z);
    }
    auto root = std::vector<int>{};
    for(auto i : iota(0,n) | filter([&](auto i){ return set.a[i] == -1; })) {
        root.push_back(i);
    }
    auto d = std::vector(n,0); {
        auto dfs = [&](auto&& self,int it,int fa,int dep) -> void {
            d[it] = dep;
            for(auto const& [i,_] : a[it] | filter([&](auto const& arr){ return std::get<0>(arr) != fa; })) {
                self(self,i,it,dep + 1);
            }
        };
        for(auto i : root) {
            dfs(dfs,i,i,0);
        }
    }
    auto step = std::bit_width(std::make_unsigned_t<decltype(std::ranges::max(d))>(std::ranges::max(d)));
    auto f = std::vector(n,std::vector(step,0)); {
        auto dfs = [&](auto&& self,int it,int fa) -> void {
            f[it][0] = fa;
            for(auto p : iota(1,step)) {
                f[it][p] = f[f[it][p - 1]][p - 1];
            }
            for(auto const& [i,_] : a[it] | filter([&](auto const& arr){ return std::get<0>(arr) != fa; })) {
                self(self,i,it);
            }
        };
        for(auto i : root) {
            dfs(dfs,i,i);
        }
    }
    auto st = std::vector(n,std::vector(step,std::numeric_limits<int>::max())); {
        auto dfs = [&](auto&& self,int it,int fa) -> void {
            for(auto const& [i,w] : a[it] | filter([&](auto const& arr){ return std::get<0>(arr) != fa; })) {
                st[i][0] = w;
                for(auto p : iota(1,step)) {
                    st[i][p] = std::min(st[i][p - 1],st[f[i][p - 1]][p - 1]);
                }
                self(self,i,it);
            }
        };
        for(auto i : root) {
            dfs(dfs,i,i);
        }
    }
    auto lca = [&](int x,int y) {
        if(d[x] < d[y]) {
            std::swap(x,y);
        }
        for(auto dd = d[x] - d[y]; dd; dd -= dd & -dd) {
            x = f[x][std::countr_zero(std::make_unsigned_t<decltype(dd)>(dd))];
        }
        if(x == y) {
            return x;
        }
        for(auto p : iota(0,step) | reverse | filter([&](auto p){ return f[x][p] != f[y][p]; })) {
            std::tie(x,y) = { f[x][p],f[y][p] };
        }
        return f[x][0];
    };
    int q;
    std::cin >> q;
    for(int x,y; auto i : iota(0,q)) {
        std::cin >> x >> y;
        --x,--y;
        if(not set.same(x,y)) {
            std::cout << -1 << '\n';
            continue;
        }
        auto u = lca(x,y);
        auto dx = d[x] - d[u],dy = d[y] - d[u];
        auto lg = [&]<std::integral T>(T num) {
            return std::bit_width(std::make_unsigned_t<T>(num));
        };
        auto const lgx = lg(dx),lgy = lg(dy);
        auto xmin = std::numeric_limits<decltype(d)::value_type>::max(),ymin = xmin;
        // for(; dx; dx -= dx & -dx) {
        //     auto p = std::countr_zero(std::make_unsigned_t<decltype(dx)>(dx));
        //     xmin = std::min(xmin,st[x][p]);
        //     x = f[x][p];
        // }
        // for(; dy; dy -= dy & -dy) {
        //     auto p = std::countr_zero(std::make_unsigned_t<decltype(dy)>(dy));
        //     ymin = std::min(ymin,st[y][p]);
        //     y = f[y][p];
        // }
        for(auto p : iota(0,lgx) | reverse | filter([&](auto p){ return d[f[x][p]] >= d[u]; })) {
            xmin = std::min(xmin,st[x][p]);
            x = f[x][p];
        }
        for(auto p : iota(0,lgy) | reverse | filter([&](auto p){ return d[f[y][p]] >= d[u]; })) {
            ymin = std::min(ymin,st[y][p]);
            y = f[y][p];
        }
        std::cout << std::min(xmin,ymin) << '\n';
    }

    std::cout << std::flush;
}