

#include <bits/stdc++.h>

using i64 = long long;

template<typename T>
auto MAX = std::numeric_limits<T>::max();

auto solve() -> void
{
    int n;
    std::cin >> n;
    auto a = std::vector(n,0);
    for(auto& v : a) {
        std::cin >> v;
    }
    auto g = std::vector(n,std::vector<int>{});
    for(auto i = 1; i != n; ++i) {
        int u,v;
        std::cin >> u >> v;
        --u,--v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

}

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);

    int tt = 1;
    // std::cin >> tt;
    while(tt--) {
        solve();
    }


}