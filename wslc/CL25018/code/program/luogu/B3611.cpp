

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    using bitset = std::bitset<100>;
    auto a = std::vector(n,bitset{});
    for(auto& bs : a) {
        for(auto i = 0; i != n; ++i) {
            bool val;
            std::cin >> val;
            bs[i] = val;
        }
    }
    for(auto k = 0; k != n; ++k) {
        for(auto i = 0; i != n; ++i) {
            if(not a[i][k]) {
                continue;
            }
            a[i] |= a[k];
        }
    }
    for(auto& bs : a) {
        for(auto i = 0; i != n; ++i) {
            std::cout << bs[i] << ' ';
        }
        std::cout << '\n';
    }

}