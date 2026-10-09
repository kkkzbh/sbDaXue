

#include<bits/stdc++.h>

using namespace std::views;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    auto a = std::vector(n,0);
    for(auto& val : a) {
        std::cin >> val;
    }
    std::ranges::sort(a | reverse);
    auto b = std::vector(1,std::make_pair( a.front(),1 ));
    for(auto const& val : a | drop(1)) {
        if(auto& [v,cnt] = b.back(); val == v) {
            ++cnt;
        } else {
            b.emplace_back(val,1);
        }
    }
    auto nn = int(b.size());
    auto sum = std::reduce(a.begin(),a.end(),0);
    auto min = std::ranges::max(a);
    auto visn = 0;
    for(auto i : iota(min,sum / 2 + 1) | filter([&](auto i){ return sum % i == 0; })) {
        auto dfs = [&](auto&& self,int l,int it) -> void {
            if(visn == n) {
                if(l == i) {
                    std::cout << i << '\n';
                    std::exit(0);
                }
                return;
            }
            for(auto const first = int(std::distance(b.begin(),std::ranges::lower_bound(b | drop(it),l,std::greater{},[](auto const& arr){ return std::get<0>(arr); }))); auto j : iota(first,nn) | filter([&](auto j){ return bool(std::get<1>(b[j])); })) {
                auto& [len,cnt] = b[j];
                auto nl = l - len ? l - len : i;
                ++visn;
                --cnt;
                self(self,nl,nl == i ? 0 : j);
                ++cnt;
                --visn;
                if(len == l or l == i) {
                    return;
                }
            }
        };
        dfs(dfs,i,0);
    }
    std::cout << sum << '\n';

}