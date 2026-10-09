

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,k;
    std::cin >> n >> k;
    auto a = std::vector(k,0);
    for(auto& v : a) {
        std::cin >> v;
    }
    if(k & 1 == 0) {
        auto ans = 0LL;
        for(auto i = k - 1; i >= 1; i -= 2) {
            ans += a[i] - a[i - 1];
        }
        std::cout << ans;
        return 0;
    }
    auto pre1 = std::vector(1,0),pre2 = pre1;
    for(auto i = k - 1; i >= 1; i -= 2) {
        pre2.emplace_back(pre2.back() + a[i] - a[i - 1]);
    }
    for(auto i = 1; i < k; i += 2) {
        pre1.emplace_back(pre1.back() + a[i] - a[i - 1]);
    }
    auto ans = std::numeric_limits<int>::max();
    for(auto i = 0,tot = 0,qwq = k / 2; i < k; i += 2,++tot,--qwq) {
        auto left = pre1[tot] - pre1[0];
        auto right = pre2[qwq] - pre2[0];
        ans = std::min(ans,left + right);
    }
    if(ans == std::numeric_limits<int>::max()) {
        ans = 0;
    }
    std::cout << ans;

}