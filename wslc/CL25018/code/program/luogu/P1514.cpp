

#include<bits/stdc++.h>

using namespace std::views;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto a = std::vector(n,std::vector(m,0));
    for(auto& val : a | join) {
        std::cin >> val;
    }
    auto constexpr INF = std::numeric_limits<int>::max();
    auto constexpr null = std::make_pair(INF,-INF);
    auto dp = std::vector(n,std::vector(m,null));
    auto constexpr move = std::array{ -1,0,1,0,-1 };
    auto vis = std::vector(m,false);
    auto dfs = [&](auto&& self,int x,int y) -> decltype(null) {
        if(x == n - 1) {
            vis[y] = true;
        }
        if(dp[x][y] != null) {
            return dp[x][y];
        }
        auto ret = std::make_pair(y,y);
        auto& [l,r] = ret;
        for(auto i : iota(0,4)) {
            if(auto mx = x + move[i],my = y + move[i + 1]; mx >= 0 and my >= 0 and mx < n and my < m and a[x][y] > a[mx][my]) {
                auto [ml,mr] = self(self,mx,my);
                l = std::min(l,ml);
                r = std::max(r,mr);
            }
        }
        return dp[x][y] = ret;
    };
    for(auto i : iota(0,m)) {
        dfs(dfs,0,i);
    }
    if(auto cnt = std::ranges::count(vis,true); cnt != m) {
        std::cout << std::format("0\n{}",m - cnt);
        return 0;
    }

    auto& s = dp[0];
    std::ranges::sort(s);
    auto ans = 0;
    {
        auto it = 0,p = -1;
        for(auto const& [l,r] : s) {
            if(it >= l) {
                p = std::max(p,r);
            } else {
                it = std::exchange(p,std::max(p,r)) + 1;
                ++ans;
            }
        }
        ans += it != m;
    }
    std::cout << std::format("1\n{}",ans);

    return 0;
}