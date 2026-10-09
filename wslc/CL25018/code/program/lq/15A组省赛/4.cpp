

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,k,t;
    std::cin >> n >> k >> t;
    auto a = std::vector(n,0ull);
    for(auto& val : a) {
        std::cin >> val;
    }
    auto ok = [&](int n) {
        auto ia = std::vector(n,0);
        std::iota(ia.begin(),ia.end(),0);
        std::sort(ia.begin(),ia.end(),[&,cmp = std::less{}](auto li,auto ri) {
            auto lv = a[li],rv = a[ri];
            return cmp(lv,rv);
        });
        #define NOT std::cout << "-1\n"; return 0;
        if(n < k) {
            return false;
        }
        auto sum2 = 0ull;
        auto sum = 0ull;
        auto que = std::deque<int>{};
        auto push = [&](int i) {
            while(not que.empty() and ia[que.back()] < ia[i]) {
                que.pop_back();
            }
            que.push_back(i);
        };
        auto pop = [&](int i) {
            if(not que.empty() and que.front() == i) {
                que.pop_front();
            }
        };
        auto top = [&]() {
            return ia[que.front()];
        };
        for(auto i = 0,bound = k - 1; i != bound; ++i) {
            auto it = ia[i];
            auto val = a[it];
            sum += val;
            sum2 += val * val;
            push(i);
        }
        auto constexpr INF = std::numeric_limits<int>::max();
        auto ans = INF;
        for(auto i = k - 1; i != n; ) {
            auto it = ia[i];
            auto val = a[it];
            sum += val;
            sum2 += val * val;
            auto avg = 1. * sum / k;
            auto sigma2 = (sum2 - k * (avg * avg)) / (k);
            push(i);
            if(sigma2 < t) {
                return true;
            }
            ++i;
            it = ia[i - k];
            val = a[it];
            sum -= val;
            sum2 -= val * val;
            pop(i - k);
        }
        return false;
    };
    auto l = 1,r = n + 1;
    while(l != r) {
        auto mid = (l + r) / 2;
        if(ok(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    if(l == n + 1) {
        NOT;
    }
    std::cout << l << '\n';

}