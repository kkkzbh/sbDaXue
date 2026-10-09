

import std;

using namespace std::views;

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    auto a = std::vector(n * 2,0);
    auto index = std::vector(std::from_range,iota(0,2 * n));
    std::ranges::sort(index,{},[&a](auto const i) noexcept { return a[i]; });
    auto k = std::string(n * 2,0);
    for(auto l = 0,r = n * 2 - 1; l < r; ++l,--r) {
        auto [min,max] = std::ranges::minmax(index[l],index[r]);
        k[min] = '(';
        k[max] = ')';
    }
    std::cout << k;

}