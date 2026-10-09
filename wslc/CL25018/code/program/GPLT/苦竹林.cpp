

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto a  = std::vector(n,0);
    for(auto& val : a) {
        std::cin >> val;
    }
    std::sort(a.begin(),a.end());
    auto ans = std::numeric_limits<int>::max();
    for(auto l = 0,r = m; r <= n; ++l,++r) {
        ans = std::min(ans,a[r - 1] - a[l]);
    }
    std::cout << ans;

}