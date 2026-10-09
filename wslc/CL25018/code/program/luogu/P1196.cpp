

import std;

template<typename Container,typename Weighter>
struct disjoint_set
{

    explicit disjoint_set(Container& a,Weighter& d) : a{ a },d{ d } {}

    auto find(auto i) -> int
    {
        if(a[i] < 0) {
            return i;
        }
        d[i] += d[std::exchange(a[i],find(a[i]))];
        return a[i];
    }

    auto merge(auto x,auto y) -> bool
    {
        auto fx = find(x),fy = find(y);
        if(fx == fy) {
            return false;
        }
        d[fx] = -a[fy];
        a[fy] += a[fx];
        a[fx] = fy;
        return true;
    }

    auto same(auto x,auto y) -> bool
    { return find(x) == find(y); }

    auto size(auto x,auto y) -> int
    { return std::abs(d[x] - d[y]) - 1; }

    Container& a;
    Weighter& d;
};

#ifndef ONLINE_JUDGE
#include <cassert>
#endif

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke([] noexcept {
        int n;
        std::cin >> n;
        using namespace std::views;
        auto a = std::vector(n,-1);
        auto d = std::vector(n,0);
        auto set = disjoint_set{ a,d };
        for(auto i : iota(0) | take(n)) {
            char c;
            int x,y;
            std::cin >> c >> x >> y;
            --x,--y;
            switch(c) {
                case 'M': {
                    set.merge(x,y);
                    break;
                } case 'C': {
                    if(not set.same(x,y)) {
                        std::println("{}",-1);
                        break;
                    }
                    std::println("{}",set.size(x,y));
                    break;
                } default: {
                    #ifndef ONLINE_JUDGE
                    assert(false);
                    #endif
                }

            }
        }
    });
}

