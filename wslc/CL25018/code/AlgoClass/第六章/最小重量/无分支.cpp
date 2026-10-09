

#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>

using namespace std::views;

using node = std::array<int,2>; // w,c

auto main() -> int
{
    auto scan = []<typename T>(T& v){ std::cin >> v; };
    int n,m,d;
    std::cin >> n >> m >> d;
    auto a = std::vector(n,std::vector(m,node{}));
    std::ranges::for_each(a | join | values,scan);
    std::ranges::for_each(a | join | keys,scan);
    auto constexpr INF = std::numeric_limits<int>::max() >> 1;
    auto path = std::vector<int>{};
    auto ans = INF;
    std::invoke([&, p = std::vector<int>{}](this auto&& self, int i, int cost, int weight) { // NOLINT
        if(i == n) {
            if(weight < ans) {
                ans = weight;
                path = p;
            }
            return;
        }
        auto r = iota(0, m) | filter([&](auto k) { return cost + a[i][k][1] <= d and weight + a[i][k][0] < ans; });
        if(r.empty()) {
            return;
        }
        for(auto k : r) {
            p.push_back(k + 1);
            self(i + 1, cost + a[i][k][1], weight + a[i][k][0]);
            p.pop_back();
        }
    }, 0, 0, 0);

    std::cout << ans << '\n';
    std::ranges::copy(path, std::ostream_iterator<int>(std::cout, " "));

}