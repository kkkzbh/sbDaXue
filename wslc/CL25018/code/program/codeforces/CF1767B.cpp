

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while(t--) {
        int n;
        std::cin >> n;
        auto a = std::vector(n,0);
        for(auto& val : a) {
            std::cin >> val;
        }
        using namespace std::views;
        auto& ans = a[0];
        std::ranges::sort(a | drop(1));
        for(auto& val : a | drop(1)) {
            if(val <= ans) {
                continue;
            }
            auto v = ans + val;
            if(v & 1) {
                ans = v / 2 + 1;
                val = v / 2;
            } else {
                ans = v / 2;
                val = v / 2;
            }
        }
        std::cout << ans << '\n';
    }


}