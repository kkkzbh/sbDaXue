

#include <bits/stdc++.h>

using namespace std::views;
using i64 = long long;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int x,y;
    std::cin >> x >> y;
    if(std::gcd(x,y) == 1) {
        std::cout << 0 << '\n';
        return 0;
    }
    int k;
    for(auto i : iota(2,100000000)) {
        if(x % i == 0 and y % i == 0) {
            k = i;
            break;
        }
    }
    auto c1 = x / k;
    auto c2 = y / k;
    auto ans = 1LL * c1 * c2;
    std::cout << ans << '\n';

}