

#include<iostream>
#include<print>
#include<vector>
#include<algorithm>
#include<ranges>
#include<numeric>
#include<functional>

#define fun auto
#define let auto
#define in :

using namespace std::views;

auto constexpr INF = std::numeric_limits<int>::max() / 2;

fun main() -> int
{
    let scan = []<typename T>(T& v) { std::cin >> v; };
    int n,m,d;
    std::cin >> n >> m >> d;
    let w = std::vector(n,std::vector(m,0)),c = w; // NOLINT
    std::ranges::for_each(c | join,scan);
    std::ranges::for_each(w | join,scan);

    auto [path,ans] = std::invoke([&,
         dp = std::vector(n,std::vector(d,std::pair{ std::vector<int>{},-1}))]
         (this auto&& self,int i,int cost) -> std::pair<std::vector<int>,int> { // NOLINT
        if(i == n) {
            return { {},0 };
        }
        auto r = iota(0,m) | filter([&](auto k){ return c[i][k] + cost <= d; });
        if(r.empty()) {
            return { {},INF };
        }
        if(auto const& [p,v] = dp[i][cost]; v != -1) {
            return dp[i][cost];
        }
        return dp[i][cost] = std::ranges::min(r | transform([&](auto k) {
            auto [p,v] = self(i + 1,cost + c[i][k]);
            p.push_back(k);
            v += w[i][k];
            return std::make_pair(std::move(p),v);
        }),{},[](auto const& nd) {
            auto const& [p,v] = nd;
            return v;
        });

    },0,0);

    std::cout << ans << '\n';
    std::ranges::for_each(path | reverse,[](auto v){ std::cout << v + 1 << ' '; });

    return 0;
}