

import std;

using namespace std::views;
auto constexpr mod = 10000;

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke([] static noexcept {
        int n,m,s,t,t0;
        std::cin >> n >> m >> s >> t >> t0;
        [[assume(s >= 1 and t >= 1)]];
        --s,--t;
        auto a = std::vector(n,std::vector<std::pair<int,int>>{});
        auto id = std::vector(n,0);
        for(auto i : iota(0) | take(m)) {
            int x,y,w;
            std::cin >> x >> y >> w;
            [[assume(x >= 1 and y >= 1)]];
            --x,--y;
            a[x].emplace_back(y,w);
            ++id[y];
        }
        auto dp = std::vector(n,0),cnt = dp;
        cnt[s] = 1;
        std::invoke([&](this auto&& self,int i,auto w) noexcept -> void {
            for(auto const& [v,ww] : a[i]) {
                [[assume (cnt[i] >= 0 and cnt[v] >= 0 and dp[i] >= 0 and dp[v] >= 0 and w >= 0)]];
                (cnt[v] += cnt[i]) %= mod;
                (dp[v] += dp[i] + static_cast<std::int64_t>(cnt[i]) * ww) %= mod;
                [[assume(id[v] >= 1)]];
                if(not --id[v]) {
                    [[assume(w >= 0 and ww >= 0)]];
                    self(v,(w + ww) % mod);
                }
            }
        },s,0);
        std::println("{}",(dp[t] + (cnt[t] - 1) * t0) % mod);

    });
}
