

#include<bits/stdc++.h>

using namespace std::views;
auto constexpr null = -1;

auto main() -> int
{
    int p,n;
    std::cin >> p >> n;
    auto a = std::map<int,int>{},v = a;
    for(int site,val,next; auto i : iota(0,n)) {
        std::cin >> site >> val >> next;
        a[site] = next;
        v[site] = val;
    }
    auto set = std::set<int>{};
    auto ans = std::vector<std::pair<int,int>>{},rep = ans;
    for(auto i = p; i != null; i = a[i]) {
        if(auto const& val = v[i]; set.contains(std::abs(val))) {
            rep.emplace_back(i,val);
        } else {
            ans.emplace_back(i,val);
            set.insert(std::abs(val));
        }
    }
    auto build = [&](auto& vec) {
        auto list = std::map<int,std::pair<int,int>>{};
        if(vec.size() == 1) {
            auto const& [s,v] = vec.front();
            list[s] = { v,null };
            return std::make_pair(s,std::move(list));
        }
        for(auto const& [pre,next] : vec | adjacent<2>) {
            auto const& [s1,v1] = pre;
            auto const& [s2,v2] = next;
            list[s1] = { v1,s2 };
            list[s2] = { v2,null };
        }
        return std::make_pair(vec.empty() ? null : std::get<0>(vec.front()),std::move(list));
    };
    auto [p1,list1] = build(ans);
    auto [p2,list2] = build(rep);
    auto print = [&]<typename T>(auto p,T const& list) {
        for(auto l = const_cast<T&>(list); p != null; p = std::get<1>(l[p])) {
            auto const& [val,next] = l[p];
            std::print("{:05d} {} ",p,val);
            next == null ? std::println("{}",next) : std::println("{:05d}",next);
        }
    };
    print(p1,list1),print(p2,list2);
}