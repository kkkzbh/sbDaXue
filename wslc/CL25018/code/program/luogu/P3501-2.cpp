

#include <bits/stdc++.h>

#define OJ ONLINE_JUDGE

auto main() -> int
{
    #ifdef ONLINE_JUDGE
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    #endif
    int n;
    std::cin >> n;
    using namespace std::string_literals;
    auto s = ""s;
    std::cin >> s;
    auto s2 = s;
    for(auto& c : s2) {
        if(c == '1') {
            c = '0';
        } else {
            c = '1';
        }
    }
    auto constexpr P = 131;
    auto p = std::vector(n + 1,0ull);
    p[0] = 1;
    using namespace std::views;
    for(auto i : iota(1) | take(n)) {
        p[i] = p[i - 1] * P;
    }
    auto h1a = std::vector(n + 1,uint64_t{}),h2a = h1a;
    auto rs2 = s2 | reverse;
    auto rh2a = h2a | reverse;
    for(auto i : iota(1) | take(n)) {
        h1a[i] = h1a[i - 1] * P + s[i - 1];
        #ifndef ONLINE_JUDGE
        std::println("rs2[{}] = {}",i - 1,rs2[i - 1]);
        #endif
        rh2a[i] = rh2a[i - 1] * P + rs2[i - 1];
    }
    auto h1 = [&](int l,int r) {
        return h1a[r] - h1a[l] * p[r - l];
    };
    auto h2 = [&](int l,int r) {
        return h2a[l] - h2a[r] * p[r - l];
    };
    #ifndef ONLINE_JUDGE
    std::println("h2a[n] = {}",h2a[n]);
    std::println("h2a[n - 1] = {}",h2a[n - 1]);
    #endif
    auto ans = 0ull;
    for(auto i : iota(1,n)) {
        auto l = 0,r = std::min(i,n - i);
        while(l != r) {
            auto mid = (l + r) / 2;
            auto ok = [&]() {
                #ifndef ONLINE_JUDGE
                std::println("s1 = {},s2 = {}",s.substr(i - 1 - mid,2 * mid + 2),s2.substr(i - 1 - mid,2 * mid + 2));
                std::println("h1 = {},h2 = {}",h1(i - 1 - mid,i + mid + 1),h2(i - 1 - mid,i + mid + 1));
                auto ds = s.substr(i - 1 - mid,2 * mid + 2);
                #endif
                return h1(i - 1 - mid,i + mid + 1) == h2(i - 1 - mid,i + mid + 1);
            };
            if(ok()) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        ans += l;
    }
    std::cout << ans;

}