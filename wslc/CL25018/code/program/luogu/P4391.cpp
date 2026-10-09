

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    using namespace std::string_literals;
    auto s = ""s;
    std::cin >> s;
    auto h1a = std::vector(n + 1,0ull);
    using namespace std::views;
    auto constexpr P = 13131;
    auto p = std::vector(n + 1,0ull);
    p[0] = 1ull;
    for(auto i : iota(1,n)) {
        p[i] = p[i - 1] * P;
    }
    for(auto i : iota(1) | take(n)) {
        h1a[i] = h1a[i - 1] * P + s[i - 1];
    }
    auto h1 = [&](int l,int r) {
        return h1a[r] - h1a[l] * p[r - l];
    };
    for(auto i : iota(1) | take(n)) {
        auto key = h1(0,i);
        auto flag = true;
        auto l = i,r = i + i;
        for(; r <= n; l += i,r += i) {
            if(h1(l,r) != key) {
                flag = false;
                break;
            }
        }
        if(not flag) {
            continue;
        }
        auto leave = n % i;
        if(leave) {
            if(h1(0,leave) != h1(n - leave,n)) {
                continue;
            }
        }
        std::cout << i << '\n';
        break;
    }


}