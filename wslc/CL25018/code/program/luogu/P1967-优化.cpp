

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
    auto f = std::vector(n,std::vector(step,0)),st = std::vector(n,std::vector(step,std::numeric_limits<int>::max())); {
        auto dfs = [&](auto&& self,int it,int fa) -> void {
            for(auto const& [i,w] : a[it] | filter([&](auto const& arr){ return std::get<0>(arr) != fa; })) {
                f[i][0] = it;
                for(auto p : iota(1,step)) {
                    f[i][p] = f[f[i][p - 1]][p - 1];
                }
                st[i][0] = w;
                for(auto p : iota(1,step)) {
                    st[i][p] = std::min(st[i][p - 1],st[f[i][p - 1]][p - 1]);
                }
                self(self,i,it);
            }
        };
        for(auto i : root) {
            std::ranges::fill(f[i],i);
            dfs(dfs,i,i);
        }
    }
    auto lca = [&](int x,int y) {
        if(d[x] < d[y]) {
            std::swap(x,y);
        }
        auto min = std::numeric_limits<std::decay_t<decltype(st[0][0])>>::max();
        for(auto dd = d[x] - d[y]; dd; dd -= dd & -dd) {
            auto p = std::countr_zero(std::make_unsigned_t<decltype(dd)>(dd));
            min = std::min(min,st[std::exchange(x,f[x][p])][p]);
        }
        if(x == y) {
            return min;
        }
        for(auto p : iota(0,step) | reverse | filter([&](auto p){ return f[x][p] != f[y][p]; })) {
            min = std::min({ min,st[x][p],st[y][p] });
            std::tie(x,y) = { f[x][p],f[y][p] };
        }
        return std::min({ min,st[x][0],st[y][0] });
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
        std::cout << lca(x,y) << '\n';
    }

    std::cout << std::flush;
}