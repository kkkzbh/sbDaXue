

import std;

using namespace std::views;

struct disjoint_set
{

    explicit disjoint_set(std::integral auto n) : a(n,-1) {}

    auto find(auto i) noexcept -> int
    {
        if(a[i] == -1) {
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
        a[fx] = fy;
        return true;
    }

    auto same(auto x,auto y) noexcept -> bool
    {
        return find(x) == find(y);
    }

    std::vector<int> a;
};

using point = std::array<int,3>;

auto distance2(point const& x,point const& y) noexcept
{
    auto const& [x1,y1,z1] = x;
    auto const& [x2,y2,z2] = y;
    auto dx = static_cast<std::int64_t>(x1 - x2),dy = static_cast<std::int64_t>(y1 - y2),dz = static_cast<std::int64_t>(z1 - z2);
    return dx * dx + dy * dy + dz * dz;
}

auto solve() noexcept
{
    int n,h,r;
    std::cin >> n >> h >> r;
    auto a = std::vector(n,point{});
    std::ranges::for_each(a | join,[](auto& val) noexcept { std::cin >> val; });

    auto bfs = std::invoke([&] noexcept {
        auto que = std::queue<std::reference_wrapper<point>>{};
        auto vis = std::vector(n,false);
        for(auto const& [i,p] : zip(iota(0,n),a) | filter([&](auto const& ip) noexcept {
            auto const& [i,p] = ip;
            auto const& [x,y,z] = p;
            return std::abs(h - z) <= r;
        })) {
            que.emplace(p);
            vis[i] = true;
        }
        while(not que.empty()) {
            for(auto i : iota(0,static_cast<int>(que.size()))) {
                auto p = que.front();
                que.pop();
                auto const& [x,y,z] = p.get();
                if(z <= r) {
                    return true;
                }
                for(auto [i,p] : iota(0,n) | filter([&,p](auto i) noexcept {
                    return not vis[i] and distance2(p,a[i]) <= 4LL * r * r;
                }) | transform([&a](auto i) noexcept {
                    return std::make_pair(i,std::ref(a[i]));
                })) {
                    que.push(p);
                    vis[i] = true;
                }
            }
        }
        return false;
    });
    auto constexpr ans = std::array{ "No","Yes" };
    std::println("{}",ans[bfs]);
}

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while(t--) {
        std::invoke(solve);
    }
}

