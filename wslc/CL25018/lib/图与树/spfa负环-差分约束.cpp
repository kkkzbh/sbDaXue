

#include <bits/stdc++.h>

using namespace std::views;

auto constexpr INF = std::numeric_limits<int>::max();

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    using node = std::pair<int,int>;
    auto g = std::vector(n + 1,std::vector<node>{});
    for(auto i : iota(0,m)) {
        int x,y,w;
        std::cin >> x >> y >> w;
        --x,--y;
        g[y].emplace_back(x,w);
    }
    for(auto i : iota(0,n)) {
        g[n].emplace_back(i,0);
    }
    auto que = std::deque<int>{};
    auto inq = std::vector(n + 1,false);
    auto dis = std::vector(n + 1,INF);
    dis[n] = 0;
    auto ct = std::vector(n + 1,0);
    auto ok = true;
    que.emplace_back(n);
    while(not que.empty()) {
        auto it = que.front();
        que.pop_front();
        inq[it] = false;
        if(++ct[it] == n) {
            ok = false;
            break;
        }
        for(auto const& [v,w] : g[it]) {
            if(dis[v] <= dis[it] + w) {
                continue;
            }
            dis[v] = dis[it] + w;
            if(inq[v]) {
                continue;
            }
            inq[v] = true;
            que.emplace_back(v);
        }
    }
    if(not ok) {
        std::cout << "NO SOLUTION\n";
        return 0;
    }
    auto min = std::ranges::min(dis | take(dis.size() - 1));
    for(auto v : dis | take(dis.size() - 1)) {
        std::cout << v - min << '\n';
    }

}
