

#include <bits/stdc++.h>

using namespace std::views;
using namespace std::string_literals;
using namespace std::string_view_literals;

struct disjoint_set
{

    explicit disjoint_set(std::integral auto n) noexcept
    : n{ static_cast<unsigned>(n) }, a(n,-1) {}

    auto find(unsigned const i) noexcept -> int
    {
        if(a[i] == -1) {
            return i;
        }
        return a[i] = find(a[i]);
    }

    auto merge(unsigned const x,unsigned const y) noexcept -> void
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

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke([] static noexcept {
        auto a = std::vector(0,std::make_pair(0u,0u));
        auto m = 0u; // 颜色个数
        {
            auto map = std::map<std::string,int>{};
            auto id = [&map,&m](auto& s) {
                auto [it,ok] = map.try_emplace(std::move(s),m);
                if(ok) {
                    ++m;
                }
                return std::get<1>(*it);
            };
            auto tmp1 = ""s,tmp2 = ""s;
            while(std::cin >> tmp1 >> tmp2) {
                a.emplace_back(id(tmp1),id(tmp2));
            }
        }
        auto set = disjoint_set{ m };
        auto deg = std::vector(m,0u);
        for(auto const& [x,y] : a) {
            set.merge(x,y);
            ++deg[x],++deg[y];
        }
        auto const odd = std::ranges::count_if(deg,[](auto const& val) static noexcept {
            return val & 1;
        });
        if(odd != 2 and odd or set.n > 1) {
            std::println("Impossible");
            return;
        }
        std::println("Possible");
    });
}