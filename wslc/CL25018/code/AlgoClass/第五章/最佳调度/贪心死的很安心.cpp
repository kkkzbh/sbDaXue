

#include<iostream>
#include<ranges>
#include<algorithm>
#include<vector>
#include<numeric>
#include<functional>
#include<print>
#include<ext/pb_ds/priority_queue.hpp>

using namespace std::views;

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

    std::println("{}",ans);

}