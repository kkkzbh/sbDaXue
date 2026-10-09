

import std;

struct fenwick
{

    using value_type = int;
    using sum_type = int;

    explicit fenwick(std::integral auto n) : d(n + 1,0) {}

    auto add(int i,auto val) noexcept -> void
    {
        for(++i; i < d.size(); i += i & -i) {
            d[i] += val;
        }
    }

    auto sum(int i) noexcept -> sum_type
    {
        auto ret = sum_type{};
        for(; i; i -= i & -i) {
            ret += d[i];
        }
        return ret;
    }

    auto sum(int x,int y) -> sum_type
    { return sum(y) - sum(x); }

    std::vector<value_type> d;
};

using namespace std::views;

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke([] noexcept {
        int n;
        std::cin >> n;
        auto a = std::vector(n,0);
        for(auto& val : a) {
            std::cin >> val;
        }
        auto map = std::unordered_map<int,int>{};
        {
            auto b = a;
            std::ranges::sort(b | reverse);
            auto [beg,end] = std::ranges::unique(b);
            b.erase(beg,end);
            for(auto [i,val] : zip(iota(0) | take(b.size()),b)) {
                map[val] = i;
            }
        }
        auto fw = fenwick{ n };
        auto sum = 0LL;
        for(auto val : a) {
            auto id = map[val];
            sum += fw.sum(id);
            fw.add(id,1);
        }
        std::println("{}",sum);
    });
}


