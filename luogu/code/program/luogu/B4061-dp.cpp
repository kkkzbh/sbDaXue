

#include<bits/stdc++.h>

using namespace std::views;

auto main() -> int
{
    int n;
    std::cin >> n;
    auto a = std::vector(n,std::vector<int>{});
    for(auto i : iota(1,n)) {
        int x,y;
        std::cin >> x >> y;
        --x,--y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    auto dp = std::vector(n,0);
    auto path = std::vector(n,0);
    auto dfs = [&](auto&& self,int it,int fa) -> void {
        for(auto i : a[it] | filter([&](auto i){ return i != fa; })) {
            self(self,i,it);
            path[i] = std::max(path[i],dp[it] + dp[i] + 1);
            dp[it] = std::max(dp[it],dp[i] + 1);
        }
    };
    dfs(dfs,0,-1);
    std::cout << std::ranges::max(path);


}