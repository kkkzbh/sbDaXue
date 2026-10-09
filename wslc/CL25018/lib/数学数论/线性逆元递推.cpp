

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,p;
    std::cin >> n >> p;
    auto pv = std::vector(n + 1,0);
    pv[1] = 1;
    for(auto i : std::views::iota(2) | std::views::take(n - 1)) {
        pv[i] = p - 1LL * pv[p % i] * (p / i) % p;
    }
    for(auto i : std::views::iota(1,n + 1)) {
        std::cout << pv[i] << '\n';
    }

}