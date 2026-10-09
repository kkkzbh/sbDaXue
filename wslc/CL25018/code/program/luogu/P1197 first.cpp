

import std;

using namespace std::views;

struct disjoint_set
{

    explicit disjoint_set(std::integral auto n,std::set<int> const& ko) noexcept : n{ n }, a(n,-1),ko{ ko } {}

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
    std::set<int> const& ko;
};

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto a = std::vector(m,std::array<int,2>{});
    for(auto& [x,y] : a) {
        std::cin >> x >> y;
    }
    int k;
    std::cin >> k;
    auto atk = std::vector(k,0);
    for(auto& val : atk) {
        std::cin >> val;
    }
    std::ranges::reverse(atk);
    auto mi = std::unordered_map<int,int>{};
    auto ko = std::unordered_set<int>{};
    for(auto const& [i,val] : zip(iota(0) | take(k),atk)) {
        mi[val] = i + 1;
        ko.insert(val);
    }
    auto ia = std::vector(std::from_range,iota(0) | take(m));
    auto lv = [&](auto const& p) noexcept {
        auto const& [x,y] = p;
        return std::ranges::max(mi[x],mi[y]);
    };
    std::ranges::sort(ia,{},[&](auto i) noexcept { return lv(a[i]); });
    auto set = disjoint_set{ n,ko };
    auto ans = std::vector(k + 1,0);
    auto it = 0;
    for(auto i : iota(0) | take(k + 1)) {
        while(it != ia.size() and lv(a[ia[it]]) == i) {
            auto const& [x,y] = a[ia[it++]];
            set.merge(x,y);
        }
        if(i) {
            ko.erase(atk[i - 1]);
        }
        ans[i] = set.count() - ko.size();
    }
    for(auto const& val : ans | reverse) {
        std::println("{}",val);
    }

}


