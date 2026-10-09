

#include <bits/stdc++.h>

using namespace std::views;
using i64 = long long;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    for(auto _ : iota(0,t)) {
        int l,r;
        std::cin >> l >> r;
        if(2 * l > r) {
            std::cout << 0 << '\n';
            continue;
        }
        auto v = r - 2LL * l + 1LL;
        std::cout << (v + 1LL) * v / 2LL << '\n';
    }

}