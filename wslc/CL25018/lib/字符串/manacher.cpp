#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
    using namespace std::string_literals;
    auto s = ""s;
    std::cin >> s;
    auto s2 = std::string(2 * s.size() + 3, 0);
    auto n = 0;
    s2[n++] = '$';
    s2[n++] = '#';
    for(auto c : s) {
        s2[n++] = c;
        s2[n++] = '#';
    }
    s2[n++] = '@';
    auto p = std::vector(n,1);
    auto c = 0,r = 0;
    using namespace std::views;
    for(auto i : iota(1,n)) {
        if(i < r) {
            p[i] = std::min(p[2 * c - i],r - i);
        }
        while(s2[i - p[i]] == s2[i + p[i]]) {
            ++p[i];
        }
        if(p[i] + i > r) {
            r = p[i] + i;
            c = i;
        }
    }
    std::cout << std::ranges::max(p) - 1;


}
