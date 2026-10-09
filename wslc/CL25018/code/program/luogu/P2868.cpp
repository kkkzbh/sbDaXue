

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto f = std::vector(n,0);
    for(auto& val : f) {
        std::cin >> val;
    }
    using side = std::tuple<int,int,int>;
    auto a = std::vector(m,side{});
    using namespace std::views;
    for(auto& [x,y,w] : a) {
        std::cin >> x >> y >> w;
        --x,--y;
    }
    auto l = 0.,r = std::reduce(f.begin(),f.end(),0.);
    auto spfa = [&](double mid) {
        using side = std::pair<int,double>;
        auto g = std::vector(n,std::vector<side>{});
        for(auto const& [x,y,w] : a) {
            g[x].emplace_back(y,mid * w - f[y]);
        }
        auto que = std::deque<int>{};
        auto constexpr INF = std::numeric_limits<double>::max() / 2;
        auto dis = std::vector(n,INF);
        auto constexpr first = 3;
        dis[first] = 0;
        que.push_front(first);
        auto inque = std::vector(n,false);
        inque[first] = true;
        auto ct = std::vector(n,0);
        ++ct[first];
        while(not que.empty()) {
            auto it = que.front();
            que.pop_front();
            inque[it] = false;
            for(auto const& [i,w] : g[it]) {
                if(dis[it] + w >= dis[i]) {
                    continue;
                }
                dis[i] = dis[it] + w;
                if(not inque[i]) {
                    que.push_back(i);
                    inque[i] = true;
                    if(++ct[i] > n) {
                        return true;
                    }
                }
            }
        }
        return false;
    };
    while(r - l >= 1e-3) {
        auto mid = (l + r) / 2;
        if(spfa(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    if(r < 1e-3) {
        std::cout << 0 << '\n';
        return 0;
    }
    std::cout << std::format("{:.2f}",l) << '\n';

}