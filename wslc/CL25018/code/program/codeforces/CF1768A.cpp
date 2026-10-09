

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    auto constexpr bound = 1000001;
    auto const& dp = []() -> decltype(auto) {
        auto static ret = std::array<int,bound>{};
        ret[1] = 1;
        ret[3] = 2;
        for(auto i = 5; i < bound; i += 2) {
            ret[i] = ret[i / 2] + 1;
        }
        return (ret);
    }();

    auto const& dp2 = []() -> decltype(auto) {
        auto static ret = std::array<int,bound>{};
        ret[0] = 0;
        ret[2] = 1;
        for(auto i = 4; i < bound; i += 2) {
            ret[i] = ret[i / 2] + 1;
        }
        return (ret);
    }();

    while(t--) {
        int n;
        std::cin >> n;
        auto a = std::vector(n,0);
        for(auto& val : a) {
            std::cin >> val;
        }
        auto odd = 0;
        auto buc = std::vector<int>{},buc2 = buc;
        buc.reserve(n),buc2.reserve(n);
        for(auto val : a) {
            if(not (val & 1)) {
                buc2.emplace_back(val);
                continue;
            }
            ++odd;
            buc.emplace_back(val);
        }
        if(not (odd & 1)) {
            std::cout << "0\n";
            continue;
        }
        using namespace std::views;
        auto constexpr INF = std::numeric_limits<int>::max();
        auto odv = buc.empty() ? INF : std::ranges::min(buc | transform([&](auto val){ return dp[val]; }));
        auto evv = buc2.empty() ? INF : std::ranges::min(buc2 | transform([&](auto val){ return dp2[val]; }));
        std::cout << std::min(odv,evv) << '\n';
    }
}