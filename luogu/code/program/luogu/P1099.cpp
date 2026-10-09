

#include<bits/stdc++.h>

using namespace std::views;

auto main() -> int
{
    auto rla = [](auto&& lam) {
        return [impl = std::forward<decltype(lam)>(lam)](auto&& args) -> decltype(auto) {
            return impl(impl,std::forward<decltype(args)>(args)...);
        };
    };
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,s;
    std::cin >> n >> s;
    auto a = std::vector(n,std::vector<std::array<int,2>>{});
    for(auto i : iota(1,n)) {
        int u,v,w;
        std::cin >> u >> v >> w;
        --u,--v;
        a[u].push_back({ v,w });
        a[v].push_back({ u,w });
    }


}