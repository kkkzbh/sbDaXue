

#include <bits/stdc++.h>

using namespace std::views;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    auto constexpr n = 2023;
    // dp[n] = dp[n - 1] + 2 * (dp[n - 2] + .... dp[1]) + n

    auto a = std::vector(n + 1,0);
    for(auto i : iota(1,n + 1)) {
        a[i] = i;
    }
    for(auto i : iota(2,n + 1)) {
        (a[i] += a[i - 1]) %= n;
        for(auto j : iota(1,i - 1)) {
            (a[i] += 2 * a[j]) %= n;
        }
    }
    std::cout << a[2023];

}