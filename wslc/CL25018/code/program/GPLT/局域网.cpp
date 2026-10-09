

import std;

using namespace std::views;

struct disjoint_set
{

    explicit disjoint_set(std::integral auto n) : a(n,-1) {}

    auto find(auto i) -> int
    {
        if(a[i] == -1) {
            return i;
        }
        return a[i] = find(a[i]);
    }

    auto merge(auto x,auto y) -> bool
    {
        auto fx = find(x),fy = find(y);
        if(fx == fy) {
            return false;
        }
        a[fx] = fy;
        return true;
    }

    auto same(auto x,auto y) -> bool
    { return find(x) == find(y); }

    std::vector<int> a;
};

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,k;
    std::cin >> n >> k;
    auto sum = 0;
    auto a = std::vector(k,std::array<int,3>{});
    for(auto& [x,y,m] : a) {
        std::cin >> x >> y >> m;
        --x,--y;
        sum += m;
    }
    std::ranges::sort(a,{},[](auto const& arr){ return std::get<2>(arr); });
    auto val = 0;
    auto set = disjoint_set{ n };
    for(auto [x,y,m] : a) {
        if(not set.merge(x,y)) {
            continue;
        }
        val += m;
    }
    std::cout << sum - val;

}