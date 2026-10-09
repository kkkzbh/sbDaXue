

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    using i64 = long long;
    i64 n;
    i64 k;
    std::cin >> n >> k;
    auto a = std::vector(n,0);
    for(auto& val : a) {
        std::cin >> val;
    }
    auto v = 0;
    for(auto val : a) {
        v ^= val;
    }
    auto b = std::vector(n,0);
    for(auto i = 0; i != n; ++i) {
        b[i] = v ^ a[i];
    }
    if(n & 1) {
        for(auto val : b) {
            std::cout << val << ' ';
        }
        return 0;
    }
    for(auto val : (k & 1 ? b : a)) {
        std::cout << val << ' ';
    }

}