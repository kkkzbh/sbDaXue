

#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>
#include<ranges>
#include<numeric>
#include<print>
#include<functional>
#include<set>

using node = std::pair<std::vector<int>,std::set<int>>;

auto main() -> int
{
    int n;
    std::cin >> n;
    auto a = std::vector(n,node{});
    auto insert = [&](int v) {
        auto const it = std::ranges::find_if(a,[&](auto const& set){ return !set.contains(v); },[](auto const& nd) {
            auto const& [vec,set] = nd;
            return set;
        });
        if(it == a.end()) {
            return false;
        }
        auto& [vec,set] = *it;
        for(auto const& val : vec) {
            set.insert(val + v);
        }
        vec.push_back(v);
        return true;
    };
    auto i = 0;
    while(std::invoke([&] mutable {
      return insert(++i);
    }));
    std::println("{}",i);
    std::ranges::for_each(a,[](auto const& vec) {
       std::ranges::for_each(vec,[](auto val){ std::print("{} ",val); });
        std::println();
    },[](auto const& nd) {
        auto const& [vec,set] = nd;
        return vec;
    });
}