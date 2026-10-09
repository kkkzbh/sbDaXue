

#include <bits/stdc++.h>

using namespace std::views;
using namespace std::string_literals;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    auto s = ""s;
    std::cin >> s;
    auto next = std::vector(s.size() + 1,0);
    next[0] = -1;
    for(auto i : iota(2,n + 1)) {
        auto it = next[i - 1];
        while(it != -1 and s[i - 1] != s[it]) {
            it = next[it];
        }
        next[i] = it + 1;
    }
    std::cout << n - next[n];

}