

#include <bits/stdc++.h>

using namespace std::views;
using namespace std::string_literals;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    auto a = ""s,b = ""s;
    std::cin >> a >> b;
    auto next = [&]() {
        auto n = int(b.size());
        auto next = std::vector(n,0);
        next[0] = n;
        auto l = 0,r = 0;
        for(auto i : iota(1,n)) {
            if(i + next[i - l] < r) {
                next[i] = next[i - l];
            } else {
                next[i] = std::max(0,r - i);
                while(i + next[i] < n and b[next[i]] == b[i + next[i]]) {
                    ++next[i];
                }
                l = i,r = i + next[i];
            }
        }
        return next;
    }();
    auto ans1 = 0LL;
    for(auto i : iota(0) | take(b.size())) {
        ans1 ^= (i + 1LL) * (next[i] + 1LL);
    }

    std::cout << ans1 << '\n';

    auto extend = [&]() {
        auto n = int(a.size()),m = int(b.size());
        auto nm = std::min(n,m);
        auto extend = std::vector(n,0);
        while(extend[0] != nm and a[extend[0]] == b[extend[0]]) {
            ++extend[0];
        }
        auto l = 0,r = extend[0];
        for(auto i : iota(1,n)) {
            if(i + next[i - l] < r) {
                extend[i] = next[i - l];
            } else {
                extend[i] = std::max(0,r - i);
                while(i + extend[i] < n and extend[i] < m and a[i + extend[i]] == b[extend[i]]) {
                    ++extend[i];
                }
                l = i,r = i + extend[i];
            }
        }
        return extend;
    }();

    auto ans2 = 0LL;
    for(auto i : iota(0) | take(a.size())) {
        ans2 ^= (i + 1LL) * (extend[i] + 1LL);
    }

    std::cout << ans2 << '\n';

}