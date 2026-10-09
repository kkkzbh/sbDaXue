

#include <bits/stdc++.h>

using namespace std::views;
using namespace std::string_literals;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    auto s = ""s;
    auto ms = ""s;
    std::cin >> s >> ms;
    auto next = [&]() {
        auto n = int(ms.size());
        auto next = std::vector(n + 1,0);
        next[0] = -1;
        for(auto i : iota(2,n + 1)) {
            auto it = next[i - 1];
            while(it != -1 and ms[i - 1] != ms[it]) {
                it = next[it];
            }
            next[i] = it + 1;
        }
        return next;
    }();

    auto find = [&]() {
        auto n = int(s.size()),m = int(ms.size());
        auto j = 0;
        for(auto i : iota(0,n)) {
            while(j and s[i] != ms[j]) {
                j = next[j];
            }
            if(s[i] == ms[j] and ++j == m) {
                return i - m + 1;
            }
        }
        return -1;
    };

    for(auto it = find(); it != -1; it = find()) {
        s.erase(it,ms.size());
    }

    std::cout << s;

}