

#include <bits/stdc++.h>

using uint = unsigned;
using namespace std::views;

auto constexpr INF = std::numeric_limits<int>::max();
auto constexpr UINF = std::numeric_limits<uint>::max();
auto constexpr ULNF = std::numeric_limits<ulong>::max();

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    ulong h;
    uint sx,sy,sz;
    scan(h,sx,sy,sz);
    auto tmp = std::array{ sx,sy,sz };
    std::ranges::sort(tmp);
    auto const [x,y,z] = tmp;
    auto dis = std::vector(x,ULNF);
    dis[0] = 0;
    using side = std::pair<int,int>;
    auto g = std::vector(x,std::vector<side>{});
    for(auto const i : iota(0u,x)) {
        for(auto const v : { y,z }) {
            g[i].emplace_back((i + v) % x,v);
        }
    }
    using qnode = std::pair<uint,ulong>;
    auto fn = std::greater{};
    auto proj = [](auto const p) {
        return p.second;
    };
    auto cmp = [fn,proj](auto const& px,auto const& py) {
        return fn(proj(px),proj(py));
    };
    auto que = std::priority_queue<qnode,std::vector<qnode>,decltype(cmp)>{ cmp };
    que.emplace(0,dis[0]);
    while(not que.empty()) {
        auto const [it,d] = que.top();
        que.pop();
        if(d > dis[it]) {
            continue;
        }
        for(auto const [v,w] : g[it]) {
            if(dis[v] <= d + w) {
                continue;
            }
            dis[v] = d + w;
            que.emplace(v,dis[v]);
        }
    }
    auto ans = 0UL;
    for(auto const v : dis) {
        if(v >= h) {
            continue;
        }
        ans += (h - v + x - 1) / x;
    }
    println("{}",ans);

}



