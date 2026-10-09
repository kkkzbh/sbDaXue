

import std;
#include <cassert>

using namespace std::views;

struct disjoint_set
{

    explicit disjoint_set(std::integral auto n) noexcept : n{ n }, a(n,-1) {}

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
        if(fx == fy) {
            return false;
        }
        a[fy] += a[fx];
        a[fx] = fy;
        --n;
        return true;
    }

    [[nodiscard]]
    auto size(auto i) noexcept -> int
    { return -a[find(i)]; }

    [[nodiscard]]
    auto count() const noexcept -> int
    { return n; }

    int n;
    std::vector<int> a;
};

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto a = std::vector(n,std::vector<int>{});
    for(auto i : iota(0) | take(m)) {
        int x,y;
        std::cin >> x >> y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    int k;
    std::cin >> k;
    auto atk = std::vector(k,0);
    for(auto& val : atk) {
        std::cin >> val;
    }
    auto ko = std::set(std::from_range,atk);
    auto set = disjoint_set{ n };
    for(auto i : iota(0) | take(n)
        | filter([&](auto i) noexcept {
            return not ko.contains(i);
        })) {
        for(auto y : a[i] | filter([&](auto y) noexcept {
            return not ko.contains(y);
        })) {
            set.merge(i,y);
        }
    }
    #ifndef ONLINE_JUDGE
    assert(set.n == n);
    #endif
    auto ans = std::vector(k,0);
    auto bns = set.count() - k;
    for(auto [i,v] : zip(iota(0) | take(k),atk | reverse)) {
        ko.erase(v);
        for(auto nd : a[v] | filter([&](auto nd) noexcept {
            return not ko.contains(nd);
        })) {
            set.merge(v,nd);
        }
        ans[i] = set.count() - k + i + 1;
    }
    for(auto const& val : ans | reverse) {
        std::println("{}",val);
    }
    std::println("{}",bns);

}


