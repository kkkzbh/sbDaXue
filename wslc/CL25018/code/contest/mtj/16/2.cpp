

#include <bits/stdc++.h>

using u32 = unsigned;
using i16 = short;

auto constexpr INF = std::numeric_limits<int>::max() / 2;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    using node = std::tuple<char,char,int>;
    int n;
    std::cin >> n;
    auto a = std::vector<node>(n);
    for(auto i = 0; i != n; ++i) {
        auto s = std::string{};
        std::cin >> s;
        a[i] = { s.front(),s.back(),s.size() };
    }
    auto p = (1 << n);
    auto dp = std::vector<std::vector<int>>(p,std::vector<int>(n));
    auto ans = 0;
    for(auto i = 1; i != p; ++i) {
        auto v = i;
        for(auto j = 0; v; ++j,v >>= 1) {
            if(not (v & 1)) {
                continue;
            }
            auto v2 = i ^ (1 << j),state = v2;
            if(not state) {
                dp[i][j] = std::get<2>(a[j]);
                continue;
            }
            for(auto k = 0; v2; ++k,v2 >>= 1) {
                if(std::get<1>(a[k]) != std::get<0>(a[j])) {
                    continue;
                }
                dp[i][j] = std::max(dp[i][j],dp[state][k] + std::get<2>(a[j]));
                ans = std::max(ans,dp[i][j]);
            }
        }
    }
    std::cout << ans << '\n';

}