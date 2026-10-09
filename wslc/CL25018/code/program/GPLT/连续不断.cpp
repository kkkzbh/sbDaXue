

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,q;
    std::cin >> n >> q;
    auto a = std::string{};
    std::cin >> a;
    auto qq = std::vector(n,0);
    for(auto i = 0; i != n; ++i) {
        if(i != n + 1 and a[i] == a[i + 1]) {
            qq[i] = 1;
        }
    }
    auto prefix = std::vector(1,0);
    prefix.reserve(n + 1);
    for(auto v : qq) {
        prefix.push_back(prefix.back() + v);
    }
    for(auto i = 0; i != q; ++i) {
        int l,r;
        std::cin >> l >> r;
        std::cout << prefix[r - 1] - prefix[l - 1] << '\n';
    }

}