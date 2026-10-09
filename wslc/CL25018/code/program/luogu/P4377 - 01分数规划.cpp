

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,bd;
    std::cin >> n >> bd;
    using node = std::pair<int,int>; // t w
    auto a = std::vector(n,node{});
    for(auto& [t,w] : a) {
        std::cin >> w >> t;
    }
    auto l = 0.;
    using namespace std::views;
    auto r = [&]() {
        return std::ranges::max(a | transform([](node const& nd) {
            auto const& [t,w] = nd;
            return (1. * t) / w;
        }));
    }();
    auto ok = [&](double mid) {
        auto b = a | transform([=](node const& nd) {
            auto const& [t,w] = nd;
            using node = std::pair<double,int>;
            return node{ t - mid * w,w };
        });
        auto constexpr INF = std::numeric_limits<double>::max() / 2;
        auto dp = std::vector(bd + 1,-INF);
        dp[0] = 0;
        for(auto i : iota(0,n)) {
            auto const& [t,w] = b[i];
            for(auto j : iota(0,bd + 1) | reverse) {
                auto it = std::min(bd,j + w);
                dp[it] = std::max(dp[it],dp[j] + t);
            }
        }
        return dp[bd] > 0;
    };
    for(auto _ : iota(0,50)) {
        auto mid = (l + r) / 2.;
        if(ok(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    std::cout << int(l * 1000) << '\n';

}