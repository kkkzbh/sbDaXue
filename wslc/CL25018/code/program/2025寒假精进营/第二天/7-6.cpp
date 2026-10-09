

import std;

using namespace std::views;

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while(t--) {
        std::invoke([] noexcept {
            int n;
            std::cin >> n;
            auto a = std::vector(n,0);
            for(auto& val : a) {
                std::cin >> val;
            }
            auto odd = 0,even = 0;
            for(auto i = 0; i < n; i += 2) {
                even += a[i];
            }
            for(auto i = 1; i < n; i += 2) {
                odd += a[i];
            }
            auto cnte = (n + 1) / 2;
            auto cnto = n / 2;
            if(even % cnte == 0 and odd % cnto == 0 and even / cnte == odd / cnto) {
                std::println("YES");
                return;
            }
            std::println("NO");
        });
    }

}