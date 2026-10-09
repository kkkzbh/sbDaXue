

#include <bits/stdc++.h>

using namespace std::views;
using namespace std::string_literals;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    auto s1 = ""s,s2 = ""s;
    std::cin >> s1 >> s2;

    auto get_next = [](std::string_view s) {
        auto n = int(s.size());
        auto next = std::vector(n + 1,0);
        next[0] = -1;
        for(auto i = 2; i <= n; ++i) {
            auto j = next[i - 1];
            while(j != -1 and s[j] != s[i - 1]) {
                j = next[j];
            }
            if(j == -1) {
                next[i] = 0;
            } else {
                next[i] = j + 1;
            }
        }
        return next;
    };

    auto kmp = [&]() {
        auto next = get_next(s2);
        auto n = int(s1.size()),m = int(s2.size());
        auto j = 0;
        for(auto i : iota(0,n)) {
            while(j and s1[i] != s2[j]) {
                j = next[j];
            }
            if(s1[i] == s2[j] and ++j == m) {
                j = next[j];
                std::cout << i - m + 2 << '\n';
            }
        }
        for(auto v : next | drop(1)) {
            std::cout << v << ' ';
        }
    };

    kmp();

}