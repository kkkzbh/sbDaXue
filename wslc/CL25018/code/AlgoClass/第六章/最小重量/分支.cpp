

#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>

using namespace std::views;

struct $0
{

    auto push_back(int val) -> void
    { a.push_back(a.back() + val); }

    auto operator()(int l,int r) const -> int   // [l,r)
    { return a[r] - a[l]; }

    std::vector<int> a{ 0 };
};

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m,bound;
    std::cin >> n >> m >> bound;
    auto a = std::vector(n,std::vector(m,std::pair<int,int>{})); // c w
    for(auto& key : a | join | keys) {
        std::cin >> key;
    }
    for(auto& val : a | join | values) {
        std::cin >> val;
    }
    auto prefix = $0{};
    prefix.a.reserve(n);
    for(auto const& vec : a) {
        prefix.push_back(std::ranges::min(vec | values));
    }
    auto que = std::invoke([&] {
        using node = std::tuple<int,int,int,int,int>; // i , d , w, buy , tot
        auto cmp = [&,cmp = std::less{},proj = [&](node const& nd) {
              return std::get<3>(nd) + prefix(std::get<0>(nd),n);
        }](node const& x,node const& y) {
            return cmp(proj(x),proj(y));
        };
        using namespace __gnu_pbds;
        using que_t = priority_queue<node,decltype(cmp)>;
        return que_t{ cmp };
    });
    using node = decltype(que)::value_type;
    auto ans = std::numeric_limits<int>::max();
    using key_t = std::pair<int,int>;
    auto pool = std::vector<std::pair<int,int>>{}; // j next
    auto constexpr null = -1;
    auto it = null;
    std::invoke([&] {
        pool.emplace_back(null,null);
        auto tot = 0;
        que.push(node{ 0,bound,0,null,0 });
        while(not que.empty()) {
            auto [i,d,w,buy,fa] = que.top();
            que.pop();
            if(d < 0 or w > ans) {
                continue;
            }
            if(i == n) {
                if(w < ans) {
                    ans = w;
                    it = fa;
                }
                continue;
            }
            for(auto j : iota(0,m)) {
                auto const& [c0,w0] = a[i][j];
                auto dd = d - c0;
                auto ww = w + w0;
                que.push(node{ i + 1,dd,ww,j,++tot });
                pool.emplace_back(j,fa);
            }
        }
    });
    std::println("{}",ans);
    auto path = std::vector<int>{};
    for(auto p = it; std::get<1>(pool[p]) != null; p = std::get<1>(pool[p])) {
        path.push_back(std::get<0>(pool[p]));
    }
    for(auto const& val : path | reverse) {
        std::print("{} ",val + 1);
    }
}