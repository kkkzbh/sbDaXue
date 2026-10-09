

#include <bits/stdc++.h>

struct hash
{
    auto static constexpr P = 131;

    explicit hash(std::string_view s) : a(s.size() + 1,uint64_t{})
    {
        if(s.size() + 1 > p.size()) {
            auto it = p.size();
            p.resize(s.size() + 1);
            while(it != p.size()) {
                p[it] = p[it - 1] * P;
                ++it;
            }
        }
        for(auto i : std::views::iota(1) | std::views::take(s.size())) {
            a[i] = a[i - 1] * P + s[i - 1];
        }
    }

    auto operator()(int l,int r) const -> uint64_t
    { return a[r] - a[l] * p[r - l]; }

    std::vector<uint64_t> a;
    std::vector<uint64_t> static inline p{ 0 };
};

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    auto a = std::vector(n,0ull);
    for(auto& v : a) {
        auto s = std::string{};
        std::cin >> s;
        v = hash{ s }(0,s.size());
    }
    std::ranges::sort(a);
    auto [first,end] = std::ranges::unique(a);
    a.erase(first,end);
    std::cout << a.size() << '\n';

}