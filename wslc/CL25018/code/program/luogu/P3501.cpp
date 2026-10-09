

#include <bits/stdc++.h>

struct hash
{

    auto static constexpr P = 131;

    auto static expand(int n) -> void
    {
        if(n + 1 > p.size()) {
            auto it = p.size();
            p.resize(n + 1);
            while(it != p.size()) {
                p[it] = p[it - 1] * P;
                ++it;
            }
        }
    }

    explicit hash(std::string_view s)
    : a(s.size() + 1,uint64_t{})
    {
        expand(s.size());
        for(auto i : std::views::iota(1) | std::views::take(s.size())) {
            a[i] = a[i - 1] * P + s[i - 1];
        }
    }

    auto operator()(int l,int r) const -> uint64_t
    { return a[r] - a[l] * p[r - l]; }

    std::vector<uint64_t> a;
    std::vector<uint64_t> static inline p{ 1 };
};

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    auto s = std::string{};
    std::cin >> s;
    auto s2 = s;
    for(auto map = std::map<char,char>{ {'1','0' },{ '0','1' } }; auto& c : s2) {
        c = map[c];
    }
    std::ranges::reverse(s2);
    auto h1 = hash(s),h2 = hash(s2);
    using namespace std::views;
    auto ans = 0ull;
    for(auto i : iota(1,n)) {
        auto l = 0,r = std::min(i,n - i);
        auto ok = [&](int mid) {
            auto i2 = n - i - 1;
            return h1(i - 1 - mid,i + mid + 1) == h2(i2 - mid,i2 + mid + 2);
        };
        auto kv = std::optional<int>{};
        while(l != r) {
            auto mid = (l + r) / 2;
            if(ok(mid)) {
                l = mid + 1;
                kv = l;
            } else {
                r = mid;
            }
        }
        ans += kv.value_or(0);
    }
    std::cout << ans;

}