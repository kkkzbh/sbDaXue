

import std;

using namespace std::views;
using namespace std::string_view_literals;

auto constexpr no = "Impossible!"sv;

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    unsigned t;
    std::cin >> t;
    while(t--) {
        std::invoke([] static noexcept {
            unsigned n,m;
            std::cin >> n >> m;
            auto a = std::vector(n,std::vector(0,0u));
            auto id = repeat(0) | take(n) | std::ranges::to<std::vector>();
            for(auto i : iota(0) | take(m)) {
                unsigned x,y;
                std::cin >> x >> y;
                --x,--y;
                // if(x == y) {
                //     continue;
                // }
                a[y].push_back(x);
                ++id[x];
            }
            auto que = iota(0u) | take(n) | filter([&](auto i) noexcept { return not id[i]; }) | std::ranges::to<std::priority_queue>();
            auto path = std::vector(0,0u);
            path.reserve(n);
            while(not que.empty()) {
                auto it = que.top();
                que.pop();
                path.push_back(it);
                for(auto v : a[it]) {
                    if(--id[v]) {
                       continue;
                    }
                    que.push(v);
                }
            }
            if(path.size() != n) {
                std::println(no);
                return;
            }
            for(auto const& val : path | reverse) {
                std::print("{} ",val + 1);
            }
            std::println();
        });
    }
}