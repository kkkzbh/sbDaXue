

#include<iostream>
#include<ranges>
#include<algorithm>
#include<vector>
#include<numeric>
#include<functional>
#include<print>
#include<random>
#include<cmath>

using namespace std::views;

auto main() -> int
{
    int n,k;
    std::cin >> n >> k;
    auto a = std::vector(n,0);
    for(auto& val : a) {
        std::cin >> val;
    }

    auto engine = std::mt19937{ std::random_device{}() };

    auto assign_rand = [&,dis = std::uniform_int_distribution{ 0,k - 1 }] mutable {
        return dis(engine);
    };
    auto real = [&,dis = std::uniform_real_distribution{ 0.,1. }] mutable {
        return dis(engine);
    };
    auto select = [&,dis = std::uniform_int_distribution{ 0,n - 1 }] mutable {
        return dis(engine);
    };

    auto ans {
            std::invoke([&] {
                auto constexpr iterations = 100000;
                auto v = std::vector(n,0);
                auto time = std::vector(k,0);
                std::ranges::generate(v,assign_rand);
                auto ans {
                        std::invoke([&] {
                            for(auto i : iota(0,n)) {
                                time[v[i]] += a[i];
                            }
                            return std::ranges::max(time);
                        })
                };
                auto T = 120.;
                auto alpha = .85;
                for(auto cnt = 0; T > 1e-6 and cnt < iterations; T *= alpha,++cnt) { // NOLINT
                    auto dx = v;
                    for(auto _ : iota(0,1)) {
                        (dx[select()] += (real() < .5 ? 1 : -1) + k) %= k;
                    }
                    for(auto i : iota(0,n)) {
                        time[dx[i]] += a[i];
                    }
                    if(auto max = std::ranges::max(time); ans > max or real() < std::exp(-(max - ans) / T)) {
                        ans = max;
                        v = std::move(dx);
                    }
                }
                return ans;
            })
    };

    std::println("{}",ans);


}