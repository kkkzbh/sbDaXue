

#include <bits/stdc++.h>

struct disjoint_set
{

    explicit disjoint_set(auto n) : n(n),a(n,-1) {}

    auto find(unsigned const i) -> unsigned
    {
        if(a[i] == -1) {
            return i;
        }
        return a[i] = find(a[i]);
    }

    auto merge(unsigned const x,unsigned const y) -> void
    {
        auto const fx = find(x),fy = find(y);
        if(fx == fy) {
            return;
        }
        a[fx] = fy;
        --n;
    }

    unsigned n;
    std::vector<int> a;
};

using namespace std::views;
using namespace std::string_view_literals;
auto constexpr no = "No"sv;

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke([] static noexcept {
        unsigned n,m;
        std::cin >> n >> m;
        auto idg = std::vector(n,0u);
        auto odg = std::vector(n,0u);
        auto set = disjoint_set{ n };
        auto a = std::vector(n,std::vector(0uz,std::make_pair(0u,false)));
        for(auto i : iota(0) | take(m)) {
            unsigned x,y;
            std::cin >> x >> y;
            --x,--y;
            a[x].emplace_back(y,false);
            set.merge(x,y);
            ++idg[y];
            ++odg[x];
        }
        for(auto& vec : a) {
            std::ranges::sort(vec);
        }
        auto const cnt = std::ranges::count_if(
            zip_transform(std::minus{},idg,odg),
            [](auto const& val) static noexcept {
                return val;
            }
        );
        if(cnt and cnt != 2 or set.n != 1) {
            std::println(no);
            return;
        }
        auto first {
            cnt ?
            std::invoke([&] noexcept {
                auto r = zip_transform(std::minus{},idg,odg);
                return static_cast<unsigned>(std::ranges::distance(
                std::ranges::begin(r),
                std::ranges::find_if(
                    r,
                    [](auto const& val) static noexcept {
                        return val == -1;
                    }
                )
            ));
            }) :
            0u
        };
        auto path = std::vector(0uz,0u);
        auto map = std::unordered_map<unsigned,unsigned>{};
        std::invoke([&](this auto&& dfs,unsigned const i) noexcept -> void {
            auto& mi = map[i];
            for(auto&& [i,v,ok] : zip(a[i] | keys | as_rvalue,a[i] | values) | enumerate | drop(mi) | filter([](auto const& p) static noexcept {
                return not std::get<2>(p);
            })) {
                ok = true;
                dfs(v);
            }
            path.push_back(i + 1);
        },first);
        for(auto const v : path | reverse) {
            std::print("{} ",v);
        }
    });

}