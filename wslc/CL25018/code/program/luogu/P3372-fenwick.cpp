

import std;

struct fenwick
{

    using value_type = std::int64_t;

    explicit fenwick(std::integral auto n) noexcept : d1(n + 1,0),d2(n + 1,0) {}

    auto add(int i,auto val) noexcept -> void ;

    auto add(int x,int y,auto val) noexcept -> void // [0,n) ?
    {
        for(auto k = x + 1; k < d1.size(); k += k & -k) {
            d1[k] += val;
            d2[k] += x * val;
        }
        for(auto k = y + 1; k < d1.size(); k += k & -k) {
            d1[k] -= val;
            d2[k] -= y * val;
        }
    }

    auto sum(int i) const noexcept -> value_type
    {
        auto ret = value_type{};
        auto ret2 = value_type{};
        for(auto k = i; k; k -= k & -k) {
            ret += d1[k];
            ret2 += d2[k];
        }
        return i * ret - ret2;
    }

    auto sum(int x,int y) const noexcept -> value_type
    { return sum(y) - sum(x); }

    std::vector<value_type> d1; // D  --------- k sD - s(i - 1)D
    std::vector<value_type> d2; // (i - 1) * D
};

using namespace std::views;

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    auto is = repeat(0) | transform([]<typename T>(T const& val) noexcept {
        std::cin >> const_cast<T&>(val);
        return val;
    });
    std::invoke([&] noexcept {
        int n,m;
        std::cin >> n >> m;
        auto fw = fenwick{ n };
        for(auto [i,val] : zip(iota(0),is) | take(n)) {
            fw.add(i,i + 1,val);
        }
        for(auto i : iota(0) | take(m)) {
            int $;
            std::cin >> $;
            if($ == 1) {
                int x,y,k;
                std::cin >> x >> y >> k;
                --x;
                fw.add(x,y,k);
            } else if($ == 2) {
                int x,y;
                std::cin >> x >> y;
                --x;
                std::println("{}",fw.sum(x,y));
            }
        }

    });
}