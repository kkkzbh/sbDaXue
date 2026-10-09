

#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;

namespace
{
    auto init = [] { // NOLINT
        std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
        return true;
    }();
}

auto main() -> int
{
    int tt;
    std::cin >> tt;
    do [] {
        int n,k;
        std::cin >> n >> n >> k;
        auto g = std::vector(n,std::vector<int>{});
        for(auto i = 1; i != n; ++i) {
            int u,v;
            std::cin >> u >> v;
            --u,--v;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        auto constexpr MOD = 998244353;
        auto pow = [](i64 v,int p) -> i64 {
            auto pv = v;
            for(; p; p >>= 1,v *= v,v %= MOD) {
                if(not (p & 1)) {
                    continue;
                }
                pv *= v;
            }
            return pv;
        };



    }(); while(--tt);


}