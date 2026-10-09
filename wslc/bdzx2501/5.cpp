

#include <bits/stdc++.h>

using i64 = long long;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int tt;
    std::cin >> tt;
    while(tt--) {
        [&]() {
            int n;
            std::cin >> n;
            auto a = std::vector(n,0);
            for(auto& v : a) {
                std::cin >> v;
            }
            auto even = [](auto v) {
                return not (v & 1);
            };
            auto map = std::unordered_map<int,int>{};
            auto el = 0;
            auto er = 0;
            for(auto v : a) {
                auto& val = map[v];
                if(val) {
                    if(not even(val)) {
                        ++er;
                    } else {
                        --er;
                    }
                }
                ++val;
            }
            auto map2 = std::unordered_map<int,int>{};

            auto ans = std::vector(n + 1,-1);
            for(auto v : a) {
                auto& val = map[v];
                --val;
                if(val) {
                    if(even(val)) {
                        ++er;
                    } else {
                        --er;
                    }
                }
                auto& val2 = map2[v];
                if((el - (val2 ? even(val2) : 0)) or (er - (val ? even(val) : 0))) {
                    ans[v] = 1;
                } else {
                    if(ans[v] == -1) {
                        ans[v] = 1;
                    }
                    ans[v] ^= 1;
                }
                if(val2) {
                    if(not even(val2)) {
                        ++el;
                    } else {
                        --el;
                    }
                }
                ++val2;
            }

            for(auto [v,cnt] : map2) {
                if(cnt != 1 and (even(cnt) or even(cnt / 2))) {
                    if(even(cnt * (cnt - 1LL) / 2)) {
                        std::cout << "No\n";
                        return;
                    }
                }
            }

            auto l = 0,r = 1;
            for(; r <= n; ++r) {
                if(r != n and a[l] == a[r]) {
                    continue;
                }
                auto len = r - l;

                if(len != map2[a[l]]) {
                    std::cout << "No\n";
                    return;
                }
                // if((len != 1 and (even(len) or even(len / 2)))) {
                //     std::cout << "No\n";
                //     return;
                // }
                l = r;
            }
            // if(std::any_of(ans.begin(),ans.end(),[](auto v) { return v == 1; })) {
            //     std::cout << "No\n";
            //     return;
            // }

            std::cout << "Yes\n";

        }();
    }

}