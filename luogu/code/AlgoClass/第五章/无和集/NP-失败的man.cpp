


#include<bits/extc++.h>

using namespace std::views;
using node = std::pair<std::vector<int>,std::set<std::pair<int,int>>>;

auto main() -> int
{
    int n;
    std::cin >> n;
    auto a = std::vector(n,node{});

    auto push_back = [&](auto const v,int const pos) {
        auto& [vec,set] = a[pos];
        for(auto const& val : vec) {
            set.emplace(val + v,v);
        }
        vec.push_back(v);
        return true;
    };
    auto pop_back = [&](int const pos) {
        auto& [vec,set] = a[pos];
        std::erase_if(set,[&](auto const& p) {
            auto const& [key,value] = p;
            return value == vec.back();
        });
        vec.pop_back();
    };

    auto ans = 0;
    auto path = std::vector(n,std::vector<int>{});
    std::invoke([&](this auto&& self,int i) -> void {
        if(i > ans) {
            ans = i;
            std::ranges::copy(a | keys,path.begin());
        }

        auto r = iota(0,n) | filter([&](auto k) {
            auto const& [vec,set] = a[k];
            return set.lower_bound({ i,0 }) == set.upper_bound({ i,std::numeric_limits<int>::max() });
        });

        std::ranges::for_each(r,[&](auto k) {   // n
           push_back(i,k);  // nlogn
           self(i + 1); // T(n + 1)
           pop_back(k);     // nlogn
        });

        // T(n) = nT(n + 1) + (n^2)logn

    },1);

    std::println("{}",ans - 1);
    std::ranges::for_each(path,[&](auto const& vec) {
       std::ranges::for_each(vec,[](auto const val){ std::print("{} ",val); });
       std::println();
    });

}