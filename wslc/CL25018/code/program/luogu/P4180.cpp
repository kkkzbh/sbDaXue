

#include <bits/stdc++.h>

struct disjoint_set
{

    explicit disjoint_set(std::integral auto n) : a(n,-1) {}

    auto find(int i) -> int
    { return a[i] == -1 ? i : a[i] = find(a[i]); }

    auto merge(int x,int y) -> bool
    {
        auto fx = find(x),fy = find(y);
        if(fx == fy) {
            return false;
        }
        a[fx] = fy;
        return true;
    }

    std::vector<int> a;
};

auto main() -> int
{
    #ifdef ONLINE_JUDGE
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    #endif
    unsigned n,m;
    std::cin >> n >> m;
    using side = std::tuple<int,int,int64_t>;
    auto a = std::vector(m,side{});
    for(auto& [x,y,w] : a) {
        std::cin >> x >> y >> w;
    }
    for(auto& [x,y,_] : a) {
        --x,--y;
    }
    std::ranges::sort(a,{},[](side const& sd){ return std::get<2>(sd); });
    auto select = std::vector(m,false);
    using namespace std::views;
    auto set = disjoint_set{ n };
    auto ans = int64_t{};
    using node = std::pair<int,int>;
    auto g = std::vector(n,std::vector<node>{});
    for(auto i : iota(0u,m)) {
        auto const& [x,y,w] = a[i];
        if(set.merge(x,y)) {
            select[i] = true;
            ans += w;
            g[x].emplace_back(y,w);
            g[y].emplace_back(x,w);
        }
    }
    auto lgn = std::bit_width(n);
    auto constexpr root = 0;
    auto constexpr INF = std::numeric_limits<int>::max() / 2;
    auto fa = std::vector(n,std::vector(lgn,root));
    auto max = fa,semax = max;
    auto d = std::vector(n,0);
    auto dfs = [&](auto&& self,int u,int father,int fw,int dep) -> void {
        fa[u][0] = father;
        max[u][0] = fw;
        semax[u][0] = -INF;
        d[u] = dep;
        for(auto p : iota(1,lgn)) {
            fa[u][p] = fa[fa[u][p - 1]][p - 1];
            auto x1 = max[u][p - 1];
            auto x2 = max[fa[u][p - 1]][p - 1];
            max[u][p] = std::max(x1,x2);
            auto cmp = x1 <=> x2;
            if(cmp == 0) {
                semax[u][p] = std::max(semax[u][p - 1],semax[fa[u][p - 1]][p - 1]);
            } else if(cmp < 0) {
                semax[u][p] = std::max(x1,semax[fa[u][p - 1]][p - 1]);
            } else {
                semax[u][p] = std::max(x2,semax[u][p - 1]);
            }
        }
        for(auto [v,w] : g[u] | filter([&](auto const& v){ return std::get<0>(v) != father; })) {
            self(self,v,u,w,dep + 1);
        }
    };
    dfs(dfs,root,root,-INF,0);
    auto lca = [&](int u,int v) {
        auto max1 = -INF,semax1 = -INF;
        auto max2 = -INF,semax2 = -INF;
        if(d[u] < d[v]) {
            std::swap(u,v);
        }
        for(auto i : iota(0,lgn) | reverse) {
            if(d[fa[u][i]] >= d[v]) {
                max1 = std::max(max1,max[u][i]);
                semax1 = std::max(semax1,semax[u][i]);
                u = fa[u][i];
            }
        }
        if(u == v) {
            return std::make_pair(max1,semax1);
        }
        for(auto i : iota(0,lgn) | reverse) {
            if(fa[u][i] != fa[v][i]) {
                max1 = std::max(max1,max[u][i]);
                max2 = std::max(max2,max[v][i]);
                semax1 = std::max(semax1,semax[u][i]);
                semax2 = std::max(semax2,semax[v][i]);
                u = fa[u][i];
                v = fa[v][i];
            }
        }
        max1 = std::max(max1,max[u][0]);
        max2 = std::max(max2,max[v][0]);
        semax1 = std::max(semax1,semax[u][0]);
        semax2 = std::max(semax2,semax[v][0]);
        return std::make_pair(std::max(max1,max2),std::max(semax1,semax2));
    };
    auto aans = std::numeric_limits<int64_t>::max() / 2;
    for(auto i : iota(0u,m) | filter([&](auto i){ return not select[i]; })) {
        auto const& [x,y,w] = a[i];
        if(x == y) {
            continue;
        }
        auto [max,semax] = lca(x,y);
        if(w == max) {
            aans = std::min(aans,ans + w - semax);
        } else {
            aans = std::min(aans,ans + w - max);
        }
    }
    #ifndef ONLINE_JUDGE
    std::println("ans = {}",ans);
    #endif
    std::cout << aans;

}