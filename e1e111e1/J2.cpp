

#include <bits/stdc++.h>

using i64 = long long;

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define DEBUG(...) __VA_ARGS__
#else
#define DEBUG(...)
#endif

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);

    auto constexpr bd = 1000000 + 2;
    auto static pv = std::array<i64,bd>{};
    for(auto i = 0; i != bd; ++i) {
        pv[i] = i * i;
    }

    int tt;
    std::cin >> tt;

    while(tt--) {
        [&]() {
            i64 n;
            std::cin >> n;
            auto ans = std::vector<i64>{};
            auto buc = std::set<i64>{};
            if(n & 1) {
                ans.emplace_back(n);
                buc.emplace(n);
                n += n;
            }
            auto sq = i64(std::sqrt(n));
            auto kv = 1LL;
            for(auto j = 2; j <= sq; ++j) {
                if(n % j == 0) {
                    kv = j;
                }
            }
            auto set = std::set{ kv,n / kv };
            while(set.size() != 1) {
                auto min = *set.begin();
                auto max = *set.rbegin();
                auto val = min * max;
                auto sq = i64(std::sqrt(val));
                if(sq * sq == val) {
                    break;
                }
                DEBUG(std::cout << std::format("{} {}\n",min,max));
                for(auto i = min; i >= 1; --i) {
                    if((min % i != 0) or buc.contains(i * max)) {
                        continue;
                    }
                    min += i;
                    buc.emplace(i * max);
                    ans.emplace_back(i * max);
                    set.erase(set.begin());
                    set.emplace(min);
                    break;
                }
            }
            std::cout << ans.size() << '\n';
            for(auto v : ans) {
                std::cout << v << ' ';
            }
            std::cout << '\n';
            DEBUG(std::cout << "-----\n");
        }();
    }
    return 0;
}
