

#include<bits/stdc++.h>

using namespace std::views;

using node = std::pair<unsigned long long,unsigned long long>;  /* i,val */

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    auto a = std::vector(n,node{});
    for(auto& [i,val] : a) {
        std::cin >> i >> val;
    }
    auto map = std::map<unsigned long long,unsigned long long>{};
    for(auto& [i,val] : a) {
        map[i] = val;
    }
    auto mm = std::ranges::max(a | transform([&](auto& nd){ return std::bit_width(nd.first); }));
    using node = std::array<unsigned long long,2>;
    auto bas = std::vector(mm,node{});
    auto zero = false;

    auto insert = [&](auto val) {
        auto id = val;
        for(auto i : iota(0,mm) | reverse | filter([&](auto i){ return static_cast<bool>(val >> i & 1); })) {
            if(bas[i][0]) {
                val xor_eq bas[i][0];
            } else {
                bas[i] = { val,id };
                return true;
            }
        }
        zero = true;
        return false;
    };

    auto ans = 0LL;
    std::ranges::sort(a | reverse,{},[](auto const& nd){ return nd.second; });
    std::ranges::for_each(a,[&](auto& nd) {
        auto const& [i,val] = nd;
        ans += insert(i) * val;
    });

    // for(auto i : iota(0,mm) | filter([&](auto i){ return static_cast<bool>(bas[i][0]); })) {
    //     ans += map[bas[i][1]];
    // }

    std::cout << ans << std::endl;

}