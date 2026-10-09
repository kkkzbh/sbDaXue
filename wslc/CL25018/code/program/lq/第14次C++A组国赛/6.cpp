

#include <bits/stdc++.h>

using i64 = long long;

struct disjoint_set
{

    explicit disjoint_set(int n) : a(n,-1),s(n,0),sv(n,0) {}

    auto find(int i) -> int
    {
        if(a[i] == -1) {
            return i;
        }
        return a[i] = find(a[i]);
    }

    auto merge(int x,int y,int w) -> void
    {
        auto fx = find(x),fy = find(y);
        if(fx == fy) {
            return;
        }
        a[fx] = fy;
        ++s[fy];
        sv[fy] += w;
    }

    auto scount(int i) -> int
    { return s[find(i)]; }

    auto svalue(int i) -> i64
    { return sv[find(i)]; }

    std::vector<int> a;
    std::vector<int> s;
    std::vector<i64> sv;
};

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    using node = std::tuple<int,int,int>;
    auto a = std::vector(n - 1,node{});
    for(auto i = 1; i != n; ++i) {
        auto& [x,y,w] = a[i - 1];
        x = i;
        std::cin >> y >> w;
        --y;
    }
    auto set = disjoint_set{ n };
    {
        auto proj = [](node const& nd){ return std::get<2>(nd); };
        auto cmp_fn = std::greater{};
        std::sort(a.begin(),a.end(),[=](node const& lnd,node const& rnd){ return cmp_fn(proj(lnd),proj(rnd)); });
    }
    for(auto const& [x,y,w] : a) {
        set.merge(x,y,w);
        if(set.scount(x) == 3) {
            std::cout << set.svalue(x) << '\n';
            break;
        }
    }

}