

#include<bits/stdc++.h>

using namespace std::views;

auto main() -> int
{
    int n;
    std::cin >> n;
    auto a = std::vector(n,std::array<double,2>{});
    for(auto& [x,y] : a) {
        std::cin >> x >> y;
    }
    a.push_back({ 0.,0. });
    auto dis = std::vector(n,std::vector(n,0.));
    auto distance = [&](int i,int j) {
        auto const& [x1,y1] = a[i];
        auto const& [x2,y2] = a[j];
        auto dx = x1 - x2,dy = y1 - y2;
        return std::sqrt(dx * dx + dy * dy);
    };
    for(auto i : iota(0,n)) {
        for(auto j : iota(i + 1,n)) {
            dis[i][j] = dis[j][i] = distance(i,j);
        }
    }


    auto dp = std::vector(n,std::vector(1 << n,std::numeric_limits<std::decay_t<decltype(dis[0][0])>>::max()));
    for(auto i : iota(0,n)) {
        dp[i][1 << i] = distance(n,i);
    }
    for(auto p : iota(1,1 << n)) {
        for(auto i : iota(0,n) | filter([&](auto i){ return bool(p >> i & 1); })) {
            for(auto kp = p ^ 1 << i; auto k : iota(0,n) | filter([&](auto k){ return bool(kp >> k & 1); })) {
                dp[i][p] = std::min(dp[i][p],dp[k][kp] + dis[k][i]);
            }
        }
    }
    std::cout << std::format("{:.2f}",std::ranges::min(iota(0,n) | transform([&](auto i){ return dp[i][(1 << n) - 1]; })));

}