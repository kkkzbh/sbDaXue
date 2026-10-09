
#include <bits/stdc++.h>

using i64 = long long;

auto constexpr INF = std::numeric_limits<int>::max();

using namespace std::views;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    auto k = std::vector(n,std::optional<int>{});
    using node = std::pair<int,int>;
    auto g = std::vector(n,std::vector<node>{});
    for(auto i : iota(0,n - 1)) {
        int u,v,w;
        std::cin >> u >> v >> w;
        g[u].emplace_back(v,w);
        g[v].emplace_back(u,w);
    }
    k[0] = 1;
    
    

    return 0;
}