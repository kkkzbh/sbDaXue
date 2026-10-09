

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    using i64 = long long;
    i64 n,k,x;
    std::cin >> n >> k >> x;
    auto a = std::vector(n,0LL);
    for(auto& v : a) {
        std::cin >> v;
    }
    for(auto& v : a) {
        auto cost = std::min(k,v / x);
        k -= cost;
        v -= cost * x;
    }
    std::sort(a.begin(),a.end(),std::greater{});
    auto ans = 0LL;
    for(auto i = k; i < n; ++i) {
        ans += a[i];
    }
    std::cout << ans;
}