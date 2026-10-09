

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    auto ans = 0LL;
    auto dp = std::vector(30,std::vector(10,-1));
    using i64 = long long;
    auto dfs = [&](auto&& dfs,int i,int s) -> i64 {
        if(s == 100) {
            return 0;
        }
        if(i == 30) {
            return s == 70;
        }
        auto is = s / 10;
        if(dp[i][is] != -1) {
            return dp[i][is];
        }
        auto ret = 0LL;
        ret += dfs(dfs,i + 1,s + 10);
        ret += dfs(dfs,i + 1,0);
        ret += s == 70;
        return dp[i][is] = ret;
    };
    std::cout << dfs(dfs,0,0);

    // std::cout << 8335366;

}