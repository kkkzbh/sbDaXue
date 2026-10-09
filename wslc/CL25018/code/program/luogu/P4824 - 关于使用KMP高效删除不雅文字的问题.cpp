

#include <bits/stdc++.h>

using namespace std::views;
using namespace std::string_literals;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    auto s = ""s,ms = ""s;
    std::cin >> s >> ms;

    auto next = [&]() {
        auto next = std::vector(ms.size() + 1,0);
        next[0] = -1;
        for(auto i : iota(2) | take(ms.size() - 1)) {
            auto it = next[i - 1];
            while(it != -1 and ms[i - 1] != ms[it]) {
                it = next[it];
            }
            next[i] = it + 1;
        }
        return next;
    }();

    auto stk = std::vector<int>{};
    auto sj = std::vector(s.size(),0);

    auto kmp = [&]() {
        auto n = int(s.size()),m = int(ms.size());
        auto j = 0;
        for(auto i : iota(0,n)) {
            stk.push_back(i);
            while(j and s[i] != ms[j]) {
                j = next[j];
            }
            if(s[i] == ms[j]) {
                ++j;
            }
            sj[i] = j;
            if(j == m) {
                stk.resize(stk.size() - m);
                if(stk.empty()) {
                    j = 0;
                } else {
                    j = sj[stk.back()];
                }
            }
        }
    };

    kmp();

    for(auto i : stk) {
        std::cout << s[i];
    }

}