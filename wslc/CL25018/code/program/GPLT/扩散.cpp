

#include <bits/stdc++.h>

struct disjoint_set
{

    explicit disjoint_set(int n) : a(n,-1) {}

    auto find(int i) -> int
    {
        if(a[i] == -1) {
            return i;
        }
        return a[i] = find(a[i]);
    }

    auto merge(int x,int y) -> bool
    {
        auto fx = find(x),fy = find(y);
        if(fx == fy) {
            return false;
        }
        a[fx] = fy;
        return true;
    }

    auto same(int x,int y) -> bool
    { return find(x) == find(y); }

    std::vector<int> a;
};

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    using point = std::pair<int,int>;
    auto a = std::vector(n,point{});
    for(auto& [x,y] : a) {
        std::cin >> x >> y;
    }
    auto dis = [&](point const& lhs,point const& rhs) {
        auto const& [x1,y1] = lhs;
        auto const& [x2,y2] = rhs;
        return std::abs(x1 - x2) + std::abs(y1 - y2);
    };
    using side = std::tuple<int,int,int>;
    auto s = std::vector<side>{};
    s.reserve(3000 * 3000);
    for(auto i = 1; i != n; ++i) {
        for(auto j = 0; j != i; ++j) {
            if(j == i) {
                continue;
            }
            s.emplace_back(i,j,dis(a[i],a[j]));
        }
    }
    {
        auto proj = [](side const& nd) {
            return std::get<2>(nd);
        };
        auto cmp_fn = std::less{};
        auto cmp = [=](side const& lhs,side const& rhs) {
            return cmp_fn(proj(lhs),proj(rhs));
        };
        std::sort(s.begin(),s.end(),cmp);
    }
    auto val = 0;
    auto set = disjoint_set{ n };
    for(auto const& [x,y,w] : s) {
        if(set.merge(x,y)) {
            val = w;
        }
    }
    std::cout << (val + 1) / 2;

}