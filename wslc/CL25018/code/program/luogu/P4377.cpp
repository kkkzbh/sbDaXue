

#include <bits/stdc++.h>

using namespace std::views;
using i64 = long long;
auto constexpr INF = std::numeric_limits<int>::max() / 2;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,w;
    std::cin >> n >> w;
    using node = std::pair<int,int>; // t,w
    auto a = std::vector(n,node{});
    for(auto& [t,w] : a) {
        std::cin >> w >> t;
    }
    // dp[i][k] k stand for ? 只需要刚溢出k就可以停止了
    // 所以2W内 一定能求得最优解
    std::ranges::sort(a,{},[](auto& p){ return std::get<1>(p); });
    auto dp = std::vector(w + 1,-INF);
    dp[0] = 0;
    auto ans = 0;
    for(auto i : iota(0,n)) {
        auto const& [t,ww] = a[i];
        for(auto j : iota(0,w + 1) | reverse) {
            if(j + ww >= w) {
                ans = std::max<i64>((dp[j] + t) * 1000LL / (j + ww),ans);
            }
            if(j < ww or dp[j - ww] + t <= dp[j]) {
                continue;
            }
            dp[j] = dp[j - ww] + t;
        }
    }
    std::cout << ans;


}