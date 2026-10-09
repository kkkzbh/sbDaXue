

#include <bits/stdc++.h>

using i64 = long long;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int tt;
    std::cin >> tt;
    while(tt--) {
        [&]() {
            int n,s;
            std::cin >> n >> s;
            auto a = std::vector(n,0);
            for(auto& v : a) {
                std::cin >> v;
            }
            auto x = i64{ s },y = x;
            for(auto v : a) {
                auto next = (x + v + 1) / 2;
                if(next > x) {
                    x = next;
                } else if(next < x) {
                    y = (y + v + 1) / 2;
                } else if(auto next2 = (y + v + 1) / 2; next2 >= y) {
                    y = next2;
                } else {
                    x = next;
                }
            }
            std::cout << std::max(x,y) << '\n';
        }();
    }

}