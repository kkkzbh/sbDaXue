

#include<iostream>
#include<vector>
#include<algorithm>
#include<ranges>
#include<numeric>
#include<functional>
#include<ext/pb_ds/priority_queue.hpp>
#include<print>

using namespace std::views;

auto main() -> int
{
    int n,k;
    std::cin >> n >> k;
    auto a = std::vector(n,0);
    for(auto& val : a) {
        std::cin >> val;
    }
    std::ranges::sort(a);
    auto prefix = std::vector(n + 1,0);
    for(auto i : iota(0,n)) {
        prefix[i + 1] = prefix[i] + a[i];
    }
    auto sum = [&](int l,int r) {
        return prefix[r] - prefix[l];
    };
    auto que {
            std::invoke([k] {
                auto r = repeat(0,k);
                auto ret = __gnu_pbds::priority_queue<int,std::greater<>>{ r.begin(),r.end() };
                return ret;
            })
    };
    while(not a.empty()) {
        auto val = que.top();
        que.pop();
        que.push(val + a.back());
        a.pop_back();
    }
    auto ans {
            std::invoke([&] {
                while(que.size() != 1) {
                    que.pop();
                }
                return que.top();
            })
    };
    std::invoke([&] {
        auto nums = std::vector(k,0);
        std::invoke([&](this auto&& self,int i) -> void { // NOLINT
            if(i == n) {
                ans = std::min(ans,std::ranges::max(nums));
            }
            for(auto j : iota(0,k) | filter([&](auto j){ return nums[j] + a[i] < ans; })) {
                nums[j] += a[i];
                self(i + 1);
                nums[j] -= a[i];
            }
        },0);
    });
    std::println("{}",ans);

}


