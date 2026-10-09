
#include<ext/pb_ds//priority_queue.hpp>

using namespace std::views;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,k;
    std::cin >> n >> k;
    auto a = std::vector(n,0);
    for(auto& val : a) {
        std::cin >> val;
    }

    auto suffix = a;
    for(auto [front,back] : suffix | reverse | pairwise) {
        back += front;
    }

    auto que = std::invoke([&suffix,k] {
        using namespace __gnu_pbds;
         // i: 该放第几个任务 s: 之前任务的安排情况 bound?(floor) -> max(s) + (总和 / k)
        using node = std::pair<int,std::vector<int>>;
        auto proj = [&suffix,k](node const& x) {
            auto const& [i,s] = x;
            return std::ranges::max(s) + suffix[i] / k;
        };
        auto cmp = [proj,impl = std::greater{}](node const& x,node const& y) {
              return impl(proj(x),proj(y));
        };
        return priority_queue<node,decltype(cmp)>{ cmp };
    });
    using node = decltype(que)::value_type;
    que.push(node{ 0,std::vector(n,0) });

    auto ans = std::numeric_limits<int>::max();
    auto tot = 0;
    while(not que.empty()) {
        auto [i,s] = que.top();
        que.pop();
        if(++tot > 4e8) {
            break;
        }
        if(i == n) {
            ans = std::min(ans,std::ranges::max(s));
            continue;
        }
        for(auto j : iota(0,k)) {
            s[j] += a[i];
            if(s[j] < ans) {
                que.push(node{ i + 1,s });
            }
            s[j] -= a[i];
        }
    }
    std::println("{}",ans);

}