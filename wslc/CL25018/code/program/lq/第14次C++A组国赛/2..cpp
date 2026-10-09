

#include <bits/stdc++.h>

using namespace std::views;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    auto val = 2ULL;
    for(auto i : iota(3,2024)) {
        auto v = val;
        for(auto j : iota(1,i)) {
            (val *= v) %= 2023ULL;
        }
    }
    std::cout << val;


}