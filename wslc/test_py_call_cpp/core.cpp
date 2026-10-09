module;

#include <algorithm>
#include <ranges>
#include <vector>

export module core;

export struct result
{
    int sum;
    bool have = false;
};

// 获取所有奇数的和
export template<std::integral T>
auto get_even_sum(std::vector<T> const& vec) -> result
{
    auto r {
        vec
        | std::views::filter([](auto v) { return v & 1; })
    };
    if(r.empty()) {
        return {};
    }
    return {
        *std::ranges::fold_left_first (
            r,
            std::plus{}
        ),
        true
    };
}