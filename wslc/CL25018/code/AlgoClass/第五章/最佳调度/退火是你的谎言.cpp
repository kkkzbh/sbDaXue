

#include<iostream>
#include<ranges>
#include<algorithm>
#include<vector>
#include<numeric>
#include<functional>
#include<print>
#include<ext/pb_ds/priority_queue.hpp>
#include<random>

using namespace std::views;

struct node
{
    int val;
    int idx;

    auto friend operator<=>(node const& n1,node const& n2)
    { return n1.val <=> n2.val; }

};

auto main() -> int
{
    int n,k;
    std::cin >> n >> k;
    auto a = std::vector<int>(n,0);
    for(auto& val : a) {
        std::cin >> val;
    }
    std::ranges::sort(a);
    auto que {
            std::invoke([k] {
                auto r = zip(repeat(0,k),iota(0,k)) | transform([](auto const& args) {
                    auto const& [val,idx] = args;
                    return node{ val,idx };
                });
                auto ret = __gnu_pbds::priority_queue<node,std::greater<>>{ r.begin(),r.end() };
                return ret;
            })
    };
    auto path = std::vector<int>{};
    while(not a.empty()) {
        auto nd = que.top();
        que.pop();
        auto& [val,idx] = nd;
        val += a.back();
        que.push(nd);
        a.pop_back();
        path.push_back(idx);
    }
    std::ranges::reverse(path);

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
                auto constexpr iterations = 10000000;
                auto& v = path;
                auto time = std::vector(k,0);
                auto ans {
                        std::invoke([&] {
                            for(auto i : iota(0,n)) {
                                time[v[i]] += a[i];
                            }
                            return std::ranges::max(time);
                        })
                };
                auto T = 100.;
                auto alpha = .9114514;
                for(auto cnt = 0; T > 1e-6 and cnt < iterations; T *= alpha,++cnt) { // NOLINT
                    auto dx = v;
                    for(auto _ : iota(0,10)) {
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