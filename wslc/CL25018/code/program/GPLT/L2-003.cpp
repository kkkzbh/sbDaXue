

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    using u32 = double;
    unsigned n,m;
    std::cin >> n >> m;
    using node = std::pair<u32,u32>;
    auto a = std::vector(n,node{});
    using namespace std::views;
    for(auto& val : a | keys ) {
        std::cin >> val;
    }
    for(auto& val : a | values) {
        std::cin >> val;
    }
    std::ranges::sort(a,[](node const& lnd,node const& rnd) {
        auto const& [cnt1,w1] = lnd;
        auto const& [cnt2,w2] = rnd;
        return 1ull * w1 * cnt2 > 1ull * w2 * cnt1;
    });
    auto ans = 0.;
    for(auto const& [cnt,w] : a) {
        if(m > cnt) {
            ans += w;
            m -= cnt;
        } else {
            ans += m * (1. * w / cnt);
            break;
        }
    }
    printf("%.2f",ans);


}