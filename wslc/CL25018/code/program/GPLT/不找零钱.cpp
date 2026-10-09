

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto a = std::vector(n,0),b = std::vector(m,0);
    for(auto& val : a) {
        std::cin >> val;
    }
    for(auto& val : b) {
        std::cin >> val;
    }
    auto n2 = 1 << n;
    auto prefix = std::vector(1,0);
    prefix.reserve(m + 1);
    for(auto& val : b) {
        prefix.emplace_back(val + prefix.back());
    }
    std::sort(a.begin(),a.end());
    auto dp = std::vector(n2 + 1,0);
    auto i = 0;
    [&]() {
        for(; i <= n2; ++i) {
            if(dp[i] == m) {
                return;
            }
            for(auto p = 0; p != n; ++p) {
                auto bit = 1 << p;
                if(i & bit) {
                    continue;
                }
                auto coin = a[p];
                auto first = dp[i];
                auto next = int(std::upper_bound(prefix.begin() + 1 + first,prefix.end(),coin + prefix[first]) - prefix.begin() - 1);
                dp[i | bit] = std::max(dp[i | bit],next);
            }
        }
    }();
    auto ans = 0;
    for(auto p = 0; p != n; ++p,i >>= 1) {
        if((i & 1) == 0) {
            ans += a[p];
        }
    }
    std::cout << ans;

}