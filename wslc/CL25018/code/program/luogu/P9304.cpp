

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    auto g = std::vector(n,std::vector<int>{});
    using namespace std::views;
    for(auto i : iota(1,n)) {
        int u,v;
        std::cin >> u >> v;
        --u,--v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    auto depth = std::vector(n,0);
    {
        auto fn = [&](auto&& self,int i,int fa) -> void {
            depth[i] = depth[fa] + 1;
            auto son = [&](int v){ return v != fa; };
            for(auto v : g[i] | filter(son)) {
                self(self,v,i);
            }
        };
        fn(fn,0,0);
    }
    auto max = std::ranges::max(depth);
    auto ans = 0;
    std::cout << ans << '\n';
    for(auto i : iota(2,n + 1)) {
        if(i > max) {
            ans += 2;
        } else {
            ++ans;
        }
        std::cout << ans << '\n';
    }

}