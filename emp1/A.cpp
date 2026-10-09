

#include <bits/stdc++.h>

using namespace std::views;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    auto a = std::vector(n,0);
    for(auto& v : a) {
        std::cin >> v;
    }
    auto i = 0;
    auto it = int(std::ranges::find(a | drop(i),2) - a.begin());
    auto ans = 0;
    while(it != n) {
        auto it2 = int(std::ranges::find(a | drop(it),1) - a.begin());
        auto it3 = int(std::ranges::find(a | drop(it2),2) - a.begin());
        ans = std::max({ ans,it2 - i,it3 - i });
        i = it2;
        it = int(std::ranges::find(a | drop(i),2) - a.begin());
        it3 = int(std::ranges::find(a | drop(it2),2) - a.begin());
        ans = std::max({ ans,it2 - i,it3 - i });
    }

    std::cout << ans << '\n';

    return 0;
}