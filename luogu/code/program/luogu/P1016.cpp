

#include<iostream>
#include<vector>
#include<algorithm>
#include<ranges>
#include<functional>
#include<numeric>
#include<format>

using namespace std::views;
using node = std::array<double, 2>;

auto main() -> int
{
    auto constexpr eps = 1e-6;
    double d1, c, d2, p;
    int n;
    std::cin >> d1 >> c >> d2 >> p >> n;
    auto a = std::vector(n + 1, node{});
    a[0][0] = 0, a[0][1] = p;
    std::ranges::for_each(a | drop(1), [](auto& x) { std::cin >> x[0] >> x[1]; });
    a.push_back(node{ d1,std::numeric_limits<double>::max() });
    auto distance = [&](int x, int y) { return a[y][0] - a[x][0]; };
    auto ans = std::numeric_limits<double>::max();
    auto dfs = [&, path = std::vector<int>{ 0 }](auto&& self, int i) mutable -> void { // NOLINT
        if(i == n + 1) {
            path.push_back(n + 1);
            ans = std::min(std::invoke([&] {
                auto st = path.begin();
                auto fuel = 0.;
                auto cost = 0.;
                while(std::invoke([&] {
                    auto ceil = a[*st][0] + c * d2;
                    auto r = std::ranges::subrange(st, path.end());
                    auto find = r.begin() + 1;
                    for(auto i = find; i != r.end() and (a[*i][0] < ceil or std::abs(a[*i][0] - ceil) < eps) and a[*find][1] > ceil; ++i) {
                        if(a[*i][1] < a[*find][1]) {
                            find = i;
                        }
                    }
                    auto const& curc = a[*st][1];
                    auto const& nextc = a[*find][1];
                    if(curc < nextc) {
                        if(distance(*st, *path.rbegin()) <= c * d2) {
                            cost += std::max((distance(*st, *path.rbegin()) / d2) - fuel, 0.) * curc;
                            return false;
                        }
                        if(nextc == std::numeric_limits<double>::max()) {
                            cost = std::numeric_limits<double>::max();
                            return false;
                        }
                        cost += (c - fuel) * curc;
                        fuel = c - distance(*st, *find) / d2;
                        st = find;
                        return true;
                    }
                    fuel -= distance(*st, *find) / d2;
                    cost += std::max(-fuel,0.) * curc;
                    fuel = std::max(fuel,0.);
                    st = find;
                    return true;
                }));
                return cost;
            }), ans);
            path.pop_back();
            return;
        }
        self(self, i + 1);
        path.push_back(i);
        self(self, i + 1);
        path.pop_back();
    };
    dfs(dfs, 1);

    if(ans == std::numeric_limits<double>::max()) {
        std::cout << "No Solution";
        return 0;
    }

    std::cout << std::format("{:.2f}", ans);

}