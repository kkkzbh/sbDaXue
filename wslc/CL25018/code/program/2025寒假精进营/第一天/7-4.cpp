

import std;

using namespace std::views;

auto main() noexcept -> int
{
    auto a = [](auto i) {
        auto num = 2 * i - 1.;
        auto den = 2. * i;
        return num / den;
    };
    int n;
    std::cin >> n;
    auto ans = 0.;
    for(auto i : iota(1,n + 1)) {
        ans += a(i);
    }
    std::println("{:.2f}",ans);

}