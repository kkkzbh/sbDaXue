

#include<bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m,v;
    std::cin >> n >> m >> v;
    auto cost = std::vector(n,std::pair{ 0,0 });
    auto money = 0;
    for(auto& [b,c] : cost) {
        std::cin >> b >> c;
        money += b;
        money += c;
    }
    auto rep = std::vector(n,std::vector<int>{});
    for(auto i = 0; i != m; ++i) {
        int a,t;
        std::cin >> a >> t;
        if(a > std::get<1>(cost[t])) {
            rep[t].push_back(a - std::get<1>(cost[t])); // 纯利润
        }
    }
    for(auto& vec : rep) {
        std::sort(vec.rbegin(),vec.rend());
    }
    auto dp = std::vector(n + 1,std::vector(money + 1,0));
    for(auto i = 1; i != n + 1; ++i) {
        auto const& r = rep[i - 1];
        auto const& [b,c] = cost[i - 1];
        for(auto j = money; j != 0; --j) {
            dp[i][j] = dp[i - 1][j];
            if(rep[i - 1].empty()) {
                continue;
            }
            auto sum = 0;
            for(auto k = 0; k != int(r.size()); ++k) {
                auto price = b + (k + 1) * c;
                if(price > j) {
                    break;
                }
                sum += r[k];
                dp[i][j] = std::max(dp[i][j],dp[i - 1][j - price] + sum - b); // 纯利润
            }
        }
    }
    auto const& r = dp[n];
    auto ans = std::numeric_limits<int>::max();
    for(auto i = 1; i != money + 1; ++i) {
        if(r[i] >= v) {
            ans = i;
            break;
        }
    }
    std::cout << ans << '\n';

    return 0;
}