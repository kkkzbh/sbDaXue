

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    auto s = std::string{};
    std::cin >> s;
    auto len = int(s.size());
    auto map = std::map<std::string,int>{};
    for(auto i = 1; i <= len; ++i) {
        auto wind = std::string{};
        auto l = 0,r = l + i - 1;
        for(auto j = l; j != r; ++j) {
            wind.push_back(s[j]);
        }
        for(; r != len; ++l,++r) {
            wind.push_back(s[r]);
            ++map[wind];
            wind.erase(wind.begin());
        }
    }
    auto ans = std::vector(len + 1,0);
    for(auto const& [str,cnt] : map) {
        ++ans[cnt];
    }
    for(auto i = 1; i <= len; ++i) {
        std::cout << ans[i] << '\n';
    }
}