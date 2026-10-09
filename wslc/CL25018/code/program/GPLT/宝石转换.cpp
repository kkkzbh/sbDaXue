

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,x,y;
    std::cin >> n >> x >> y;
    auto dp1 = std::vector(n,0LL),dp2 = std::vector(n,0LL);
    --n;
    dp2[0] = 1LL;
    for(auto i = 1; i <= n; ++i) {
        dp2[i] = dp1[i - 1] + y * dp2[i - 1];
        dp1[i] = dp1[i - 1] + x * dp2[i];
    }
    std::cout << dp1[n];

}