

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while(t--) {
        unsigned n;
        std::cin >> n;
        auto a = std::vector(n,0u);
        for(auto& val : a) {
            std::cin >> val;
        }
        auto mi = std::countr_zero(n);
        using node = std::tuple<unsigned,bool,unsigned>;
        auto [ans,flag,_] = [&](this auto&& merge,int first,int i) -> node {
            if(not i) {
                return { 0,true,a[first] };
            }
            auto cnt = 1 << i;
            auto end = first + cnt;
            auto mid = (first + end) / 2;
            using namespace std::views;
            auto arr = a | drop(first) | take(1 << i);
            auto min = std::ranges::min(arr),max = std::ranges::max(arr);
            if(max - min + 1 == cnt) {
                auto [cnt1,flag1,v1] = merge(first,i - 1);
                auto [cnt2,flag2,v2] = merge(mid,i - 1);
                if(not flag1 or not flag2) {
                    goto err;
                }
                auto ct = cnt1 + cnt2 + (v1 > v2);
                return { ct,true,max };
            }
            err:
            return { {},false,{} };
        }(0,mi);
        if(not flag) {
            std::cout << "-1\n";
            continue;
        }
        std::cout << ans << '\n';
    }

}