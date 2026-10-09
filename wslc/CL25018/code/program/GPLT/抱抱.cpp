

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int a,b,c,m;
    std::cin >> a >> b >> c >> m;
    auto ka = 0,kb = ka,kc = ka;
    for(auto i = 0; i != m; ++i) {
        int op,k;
        std::cin >> op >> k;
        if(op == 1) {
            ka = std::max(ka,k);
        } else if(op == 2) {
            kb = std::max(kb,k);
        } else {
            kc = std::max(kc,k);
        }
        std::cout << (1LL * (a - ka)) * (1LL * b - kb) * (1LL * c - kc) << '\n';
    }

}