

import std;
#ifndef ONLINE_JUDGE
#include <cassert>
#endif

using namespace std::views;

template<std::integral T>
struct disjoint_set
{

    template<typename U>
    requires std::integral<typename U::value_type> and requires(U a) {
        std::span(a);
    }
    explicit disjoint_set(U& a) : a{ a } {}

    auto find(auto i) noexcept -> int
    {
        if(a[i] < 0) {
            return i;
        }
        return a[i] = find(a[i]);
    }

    auto merge(auto x,auto y) noexcept -> bool
    {
        auto fx = find(x),fy = find(y);
        #ifndef ONLINE_JUDGE
        assert(fx != fy);
        #endif
        if(fx == fy) {
            return false;
        }
        a[fy] += a[fx];
        a[fx] = fy;
        return true;
    }

    auto count(auto x) noexcept -> int
    { return -a[find(x)]; }

    std::span<T> a;
};

template<typename U>
explicit disjoint_set(U& a) -> disjoint_set<typename U::value_type>;

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,q;
    std::cin >> n >> q;
    auto a = std::vector(n - 1,std::array<int,3>{});
    for(auto& [x,y,r] : a) {
        std::cin >> x >> y >> r;
        --x,--y;
    }
    auto query = std::vector(q,std::array<int,2>{});
    for(auto& [k,v] : query | join) {
        std::cin >> k >> v;
        --v;
    }
    std::ranges::sort(a,std::greater{},[](auto const& arr) noexcept { return arr[2]; });
    auto iq = std::vector(std::from_range,iota(0,q));
    std::ranges::sort(iq | reverse,{},[&](auto i) noexcept { return query[i][0]; });
    auto it = 0;
    auto d = std::vector(n,-1);
    auto set = disjoint_set{ d };
    auto ans = std::vector(q,0);
    for(auto i : iq) {
        auto const& [k,v] = query[i];
        while(it != n and a[it][2] >= k) {
            auto const& [x,y,_] = a[it];
            set.merge(x,y);
            ++it;
        }
        ans[i] = set.count(v) - 1;
    }
    for(auto const& val : ans) {
        std::println("{}",val);
    }

}