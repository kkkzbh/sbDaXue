

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