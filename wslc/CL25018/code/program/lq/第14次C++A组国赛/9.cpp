

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,l,r;
    std::cin >> n >> l >> r;
    auto a = std::vector(n,0);
    a[0] = -1;
    for(auto i = 1; i != n; ++i) {
        int f;
        std::cin >> f;
        a[i] = --f;
    }

}