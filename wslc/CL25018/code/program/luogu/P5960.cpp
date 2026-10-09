

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    using side = std::pair<int,int>;
    auto g = std::vector(n + 1,std::vector<side>{});
    using namespace std::views;
    for(auto i : iota(0,m)) {
        int x,y,w;
        std::cin >> x >> y >> w;
        --x,--y;
        g[y].emplace_back(x,w);
    }
    for(auto i : iota(0,n)) {
        g[n].emplace_back(i,0);
    }
    auto first = n;
    auto que = std::deque<int>{};
    auto constexpr INF = std::numeric_limits<int>::max() / 2;
    auto dis = std::vector(n + 1,INF);
    dis[first] = 0;
    auto inq = std::vector(n + 1,false);
    auto ct = std::vector(n + 1,0);
    ++ct[first];
    inq[first] = true;
    que.push_front(first);
    auto ok = [&]() {
        while(not que.empty()) {
            auto it = que.front();
            que.pop_front();
            inq[it] = false;
            for(auto const& [v,w] : g[it]) {
                if(dis[it] + w >= dis[v]) {
                    continue;
                }
                dis[v] = dis[it] + w;
                if(not inq[v]) {
                    que.empty() or dis[v] > dis[que.front()] ? que.push_back(v) : que.push_front(v);
                    inq[v] = true;
                    if(++ct[v] > n + 1) {
                        return false;
                    }
                }
            }
        }
        return true;
    }();
    if(not ok) {
        std::cout << "NO\n";
        return 0;
    }
    for(auto v : dis | reverse | drop(1) | reverse) {
        std::cout << v << ' ';
    }

}