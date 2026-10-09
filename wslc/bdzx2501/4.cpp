

#include <bits/stdc++.h>

using i64 = long long;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int tt;
    std::cin >> tt;
    while(tt--) {
        [&]() {
            i64 l,r;
            std::cin >> l >> r;
            if(l == 1) {
                std::cout << 0 << '\n';
                return;
            }
            if(r - l + 1 == 1) {
                std::cout << "infty\n";
                return;
            }
            auto ans = 0LL;
            ans += l - 1;
            auto first = 2 * l - r - 1;
            if(first > 0) {
                auto q = r - l;
                auto mf = first % q;
                ans += (mf + first) * ((first - mf) / q + 1) / 2;
            }
            std::cout << ans << '\n';
        }();
    }

}