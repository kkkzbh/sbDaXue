

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
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m,f;
    std::cin >> n >> m >> f;
    using node = std::tuple<int,int,int,int>;
    auto a = std::vector(m,node{});
    using namespace std::views;
    for(auto& [u,v,c,t] : a) {
        std::cin >> u >> v >> c >> t;
        --u,--v;
    }
    auto l = 0.,r = 1. * f;
    auto ok = [&](double mid) {
        using node = std::tuple<int,int,double>;
        auto b = std::vector(m,node{});
        for(auto i : iota(0,m)) {
            auto const& [u1,v1,c1,t1] = a[i];
            b[i] = std::make_tuple(u1,v1,c1 + mid * t1);
        }
        std::ranges::sort(b,{},[](node const& nd) {
            return std::get<2>(nd);
        });
        auto set = disjoint_set{ n };
        auto ans = 0.;
        for(auto const& [u,v,w] : b) {
            if(set.merge(u,v)) {
                ans += w;
            }
        }
        return f - ans < 0;
    };
    while(r - l >= 1e-6) {
        auto mid = (l + r) / 2;
        if(ok(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    std::cout << std::format("{:4f}",l);

}