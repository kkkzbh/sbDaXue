

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while(t--) {
        using i64 = long long;
        int n,k;
        std::cin >> n >> k;
        auto a = std::vector(n,0),b = a;
        for(auto& val : a) {
            std::cin >> val;
        }
        for(auto& val : b) {
            std::cin >> val;
        }
        using namespace std::views;
        auto ans = 0;
        auto max = 0;
        auto val = 0;
        for(auto i : iota(0,std::min(k,n))) {
            val += a[i];
            max = std::max(max,b[i]);
            ans = std::max( ans,val + (k - i - 1) * max);
        }
        std::cout << ans << '\n';
    }
}