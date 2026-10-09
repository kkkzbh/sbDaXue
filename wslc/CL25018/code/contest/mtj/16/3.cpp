

#include <bits/stdc++.h>

using u32 = unsigned;
using i16 = short;

auto constexpr INF = std::numeric_limits<int>::max();

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    auto a = std::vector<int>(n);
    for(auto& v : a) {
        std::cin >> v;
    }
    std::sort(a.begin(),a.end());
    auto it = n;
    auto diff = std::vector<int>(n + 1);
    diff[1] = a[0];
    for(auto i = 1; i != n; ++i) {
        diff[i + 1] = a[i] - a[i - 1];
    }


}