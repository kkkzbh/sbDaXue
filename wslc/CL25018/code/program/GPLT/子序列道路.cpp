

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m,k;
    std::cin >> n >> m >> k;
    using side = std::tuple<int,int,int>; // x y w
    auto s = std::vector(m,side{});
    for(auto& [x,y,w] : s) {
        std::cin >> x >> y >> w;
        --x,--y;
    }
    auto a = std::vector(k,0);
    for(auto& val : a) {
        std::cin >> val;
        --val;
    }
    using i64 = long long;
    auto constexpr INF = std::numeric_limits<i64>::max();
    auto dp = std::vector(n,INF);
    dp[0] = 0LL;
    for(auto v : a) {
        auto const& [x,y,w] = s[v];
        if(dp[x] != INF) {
            dp[y] = std::min(dp[y],dp[x] + w);
        }
    }
    if(dp[n -  1] == INF) {
        std::cout << -1;
        return 0;
    }
    std::cout << dp[n - 1];

}