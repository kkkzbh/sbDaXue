

#include <bits/extc++.h>

auto main() -> int
{
    using i64 = long long;
    #define int i64
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m,s,d;
    std::cin >> n >> m >> s >> d;
    auto a = std::vector(n,int{});
    for(auto& val : a) {
        std::cin >> val;
    }
    using namespace std::views;
    using node = std::pair<int,int>;
    auto g = std::vector(n,std::vector<node>{});
    for(auto i : iota(0) | take(m)) {
        int x,y,w;
        std::cin >> x >> y >> w;
        if(x == y) {
            continue;
        }
        g[x].emplace_back(y,w);
        g[y].emplace_back(x,w);
    }
    auto constexpr INF = std::numeric_limits<int>::max() / 2;
    auto dis = std::vector(n,INF);
    dis[s] = {};
    auto cmp_fn = std::greater{};
    auto proj = [&](int i){ return dis[i]; };
    auto cmp = [=](int lhs,int rhs){ return cmp_fn(proj(lhs),proj(rhs)); };
    using namespace __gnu_pbds;
    auto que = priority_queue<int,decltype(cmp)>{ cmp };
    auto iq = std::vector(n,decltype(que)::point_iterator{});
    for(auto i : iota(0,n)) {
        iq[i] = que.push(i);
    }
    auto path = std::vector(n,-1);
    auto count = std::vector(n,0);
    auto ct = a;
    count[s] = 1;
    while(not que.empty()) {
        auto it = que.top();
        que.pop();
        if(it == d) {
            break;
        }
        for(auto [v,w] : g[it]) {
            if(dis[it] + w == dis[v]) {
                count[v] += count[it];
                if(path[v] == -1 or ct[it] + a[v] > ct[v]) {
                    ct[v] = ct[it] + a[v];
                    path[v] = it;
                }
            } else if(dis[it] + w < dis[v]) {
                dis[v] = dis[it] + w;
                que.modify(iq[v],v);
                path[v] = it;
                ct[v] = ct[it] + a[v];
                count[v] = count[it];
            }
        }
    }
    auto buc = std::vector<int>{};
    buc.reserve(n);
    for(auto it = d; it != -1; it = path[it]) {
        buc.emplace_back(it);
    }
    std::cout << count[d] << ' ' << ct[d] << '\n';
    auto r = buc | reverse;
    std::cout << r[0];
    for(auto v : r | drop(1)) {
        std::cout << ' ' << v;
    }


}