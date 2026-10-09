

#include<bits/stdc++.h>

using namespace std::views;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int m,d;
    std::cin >> m >> d;


    auto constexpr step = 18;
    auto constexpr lg2 = std::invoke([]() constexpr {
        auto lg2 = std::array<int,200000>{ 0,0,1 };
        for(auto i = 3; i != lg2.size(); ++i) {
            lg2[i] = lg2[i / 2] + 1;
        };
        return lg2;
    });

    auto st = std::vector<std::array<long,step>>{};
    auto insert = [&](auto num) {
        auto it = static_cast<int>(st.size());
        st.push_back({ num });
        for(auto p : iota(1,step)) {
            if(it >= 1 << p - 1) {
                st[it][p] = std::max(st[it][p - 1],st[it - (1 << p - 1)][p - 1]);
            } else {
                st[it][p] = st[it][p - 1];
            }
        }
    };
    auto query = [&](int l,int r) {
        auto len = r - l + 1;
        auto k = lg2[len];
        return std::max(st[r][k],st[l + (1 << k) - 1][k]);
    };

    auto t = 0LL;
    for(auto _ : iota(0,m)) {
        char c;
        int v;
        std::cin >> c >> v;
        if(c == 'A') {
            insert((v + t) % d);
        } else if(c == 'Q') {
            t = query(st.size() -  v,st.size() - 1);
            std::cout << t << '\n';
        }
    }

    std::cout << std::flush;

}