

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    auto a = std::vector(n,0),k = a;
    for(auto& v : a) {
        std::cin >> v;
    }
    for(auto& v: k) {
        std::cin >> v;
    }
    auto que = std::deque<int>{};
    auto vis = std::vector(n,false);
    que.emplace_back(0);
    vis[0] = true;
    auto now = std::vector(n,0);
    auto step = [&]() {
        auto step = 0;
        auto p = 0;
        while(not que.empty()) {
            for(auto i = 0,bound = int(que.size()); i != bound; ++i) {
                auto it = que.front();
                que.pop_front();
                if(it + k[it] >= n - 1) {
                    return step + 1;
                }
                for(auto j = std::max(p,it + 1),bound = it + k[it] + 1; j < bound; ++j) {
                    p = std::max(p,j);
                    if(vis[j - a[j]]) {
                        continue;
                    }
                    vis[j - a[j]] = true;
                    que.push_back(j - a[j]);
                }
            }
            ++step;
        }
        return -1;
    }();
    std::cout << step << '\n';

}
