

#include <bits/stdc++.h>

using namespace std::string_literals;

using i64 = long long;
using u64 = unsigned long long;

auto constexpr INF = std::numeric_limits<int>::max();
auto constexpr LNF = std::numeric_limits<i64>::max();

namespace
{
    auto init = [] { // NOLINT
        std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
        return true;
    }();
}

auto main() -> int
{
    int tt;
    std::cin >> tt;
    while(tt--) [] {
        int n,k;
        std::cin >> n >> k;
        if(k & 1) {
            lose:
            std::cout << "0\n";
            return;
        }
        auto x = (n - 1) / k;
        ++x;
        auto leave = n - 1 - k / 2;
        if(leave < 0) {
            goto lose;
        }
        auto y = leave / k;
        ++y;

        std::cout << 1ull * x * y << '\n';

    }();

}