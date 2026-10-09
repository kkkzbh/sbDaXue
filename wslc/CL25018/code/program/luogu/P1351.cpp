

#include <bits/stdc++.h>

using namespace std::views;

auto constexpr INF = std::numeric_limits<int>::max();

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    auto g = std::vector(n,std::vector<int>{});
    for(auto i : iota(1,n)) {
        int u,v;
        std::cin >> u >> v;
        --u,--v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    auto a = std::vector(n,0);
    for(auto& v : a) {
        std::cin >> v;
    }
    auto ans = 0LL;
    auto max = 0;
    auto constexpr MOD = 10007;
    for(auto i : iota(0,n)) {
        auto& vec = g[i];
        auto ma = 0,sema = 0;
        auto sum = 0,sum2 = 0;
        for(auto it : vec) {
            auto val = a[it];
            if(val > ma) {
                sema = std::exchange(ma,val);
            } else {
                sema = std::max(sema,val);
            }
            (sum += val) %= MOD;
            (sum2 += val * val) %= MOD;
        }
        max = std::max(max,ma * sema);
        (ans += (sum * sum) - sum2) %= MOD;
    }
    std::cout << max << ' ' << ans << '\n';

}
