

#include<bits/stdc++.h>

using namespace std::views;

auto main() -> int
{
    int n,m;
    std::cin >> n >> m;
    auto a = std::vector(n,std::array<int,3>{});
    for(auto ia = 0; auto& [i,x,y] : a) {
        std::cin >> x >> y;
        --x,--y;
        y += (y < x) * m;
        i = ia++;
    }
    std::ranges::sort(a,{},[](auto const& nd){ return nd[1]; });
    a.resize(n *= 2);
    std::ranges::copy(a | take(n / 2) | transform([&](auto nd){ return nd[1] += m,nd[2] += m,nd; }),a.begin() + n / 2);
    auto st = std::vector(n,std::vector(std::bit_width(static_cast<std::make_unsigned_t<decltype(n)>>(n)),0));
    auto step = static_cast<int>(st[0].size());
    std::invoke([&] {
        auto it = 0;
        auto next = [&](auto ft) {
            auto y = a[ft][2];
            for(auto ix = a[it][1]; it != n and ix <= y; ix = a[++it][1]);
        };
        std::ranges::for_each(iota(0,n),[&](auto i) {
            next(i);
            st[i][0] = it - 1;
        });
        for(auto p : iota(1,step)) {
            for(auto i : iota(0,n)) {
                st[i][p] = st[st[i][p - 1]][p - 1];
            }
        }
    });
    auto ans = std::vector(n / 2,0);
    auto query = [&](auto i) {
        auto pos = a[i][1] + m;
        auto ret = 1; // 1 是因为要包含自己
        for(auto p : iota(0,step) | reverse) {
            auto to = st[i][p],it = a[to][2];
            if(it < pos) {
                i = to;
                ret += 1 << p;
            }
        }
        return ret + 1; // + 1 是因为 要包含跳到最末尾的那个末尾
    };
    std::ranges::for_each(iota(0,n / 2),[&](auto i) {
        auto id = a[i][0];
        ans[id] = query(i);
    });
    std::ranges::for_each(ans,[](auto const& val){ std::cout << val << ' '; });

}