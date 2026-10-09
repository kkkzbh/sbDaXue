

#include<iostream>
#include<vector>
#include<algorithm>
#include<ranges>
#include<numeric>
#include<functional>
#include<format>

using node = std::array<double, 2>;
using namespace std::views;
auto static constexpr DNF = std::numeric_limits<double>::max();
auto static constexpr debug = false;

auto main() -> int
{
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
    double d1, c, d2, p;
    int n;
    std::cin >> d1 >> c >> d2 >> p >> n;
    auto a = std::vector(n + 2, node{});
    a[0][0] = 0., a[0][1] = p;
    std::ranges::for_each(a | drop(1) | take(n), [](auto& val) { std::cin >> val[0] >> val[1]; });
    a[n + 1][0] = d1, a[n + 1][1] = DNF;
    std::ranges::sort(a, {}, [](auto const& val) { return val[0]; });
    auto ans = std::invoke([&] {
        auto i = 0;
        auto fuel = 0.;
        auto cost = 0.;
        while(i != n + 1) {
            auto move = [&](auto first, auto last) {
                auto need = (a[last][0] - a[first][0]) / d2;
                if(a[last][1] < a[first][1]) {
                    auto consume = std::max(need - fuel, 0.);
                    cost += consume * a[first][1];
                    fuel = std::max(fuel - need,0.);
                } else {
                    decltype(fuel) cache;
                    auto add = last == n + 1 ? (cache = 0,need - fuel) : (cache = c - need,c - fuel);
                    fuel = cache;
                    cost += add * a[first][1];
                }
            };
            auto next = a[i][0] + c * d2;
            auto r = iota(i + 1, n + 2) | take_while([&](auto i) { return a[i][0] <= next; });

            if constexpr(debug) {
                std::cout << i << ' ' << std::format("fuel = {},cost = {}\n",fuel,cost);
                std::cout << "r = ";
                for(auto vi : r) {
                    std::cout << vi << ' ';
                }
                std::cout << "\n----------------------------\n";
            }

            if(r.empty()) {
                return DNF;
            }
            a[n + 1][1] = a[i][1];
            auto it = std::ranges::find_if(r, [&](auto v) { return v < a[i][1]; }, [&](auto i) { return a[i][1]; });
            if(it == r.end()) {
                auto ii = std::ranges::min(r, {}, [&](auto i) { return a[i][1]; });
                move(i, ii);
                i = ii;
            } else {
                move(i, *it);
                i = *it;
            }
        }
        return cost;
    });

    std::cout << (ans == DNF ? "No Solution" : std::format("{:.2f}", ans));

}