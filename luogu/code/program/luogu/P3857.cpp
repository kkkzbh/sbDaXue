

#include<iostream>
#include<vector>
#include<ranges>
#include<algorithm>
#include<numeric>
#include<functional>
#include<bitset>

using namespace std::views;

struct linera_basis_fn
{
    template<typename T>
    requires std::integral<T> or std::same_as<T, __int128>
    [[nodiscard]]
    auto static increment(std::vector<T> const& a,int m) -> std::pair<std::vector<T>,bool>
    {
        using value_type = T;
        auto ret = std::vector(m + 1,value_type{});
        auto zero = false;
        auto insert = [&ret,&zero,m](value_type val) {
            for(auto i : std::views::iota(0,m + 1) | std::views::reverse | std::views::filter([&val](auto i){ return bool(val >> i); })) {
                if(ret[i]) {
                    val ^= ret[i];
                } else {
                    ret[i] = val;
                    return;
                }
            }
            zero = true;
        };
        std::ranges::for_each(a,insert);
        return std::make_pair(ret,zero);
    }

    template<std::size_t N>
    auto static guess(std::vector<std::bitset<N>>& a,int m) -> int
    {
        auto n = int(a.size());
        auto rank = 0;
        auto const bit = std::bitset<N>{ 1ULL << (m - 1) };

        for(auto i : std::views::iota(0,m + 1)) {
            auto ir = std::views::iota(rank,n);
            auto it = *std::ranges::find_if(ir,[](auto v){ return bool(v); },[&a,&bit,i,m](auto k){ return (a[k] << i & bit).test(m - 1); });
            if(it == n) {
                continue;
            }
            if(it != rank) {
                std::ranges::swap(a[it],a[rank]);
            }
            for(auto k : std::views::iota(0,n) | std::views::filter([&a,rank,&bit,i,m](auto k){ return k != rank and (a[k] << i & bit).test(m - 1); })) {
                a[k] ^= a[rank];
            }
            if(++rank == n) {
                break;
            }
        }
        return rank;
    }

    template<typename T>
    requires std::integral<T> or std::same_as<T, __int128>
    auto static gauss(std::vector<T>& a,int m) noexcept -> int
    {
        auto n = int(a.size());
        auto rank = 0;
        auto const bit = T{ 1 } << (m - 1);
        for(auto i : std::views::iota(0,m + 1)) {
            auto ir = std::views::iota(rank,n);
            auto it = *std::ranges::find_if(ir,[](auto v){ return bool(v); },[&a,bit,i](auto k){ return a[k] << i & bit; });
            if(it == n) {
                continue;
            }
            if(it != rank) {
                std::ranges::swap(a[it],a[rank]);
            }
            for(auto k : std::views::iota(0,n) | std::views::filter([&a,rank,bit,i](auto k){ return k != rank and bool(a[k] << i & bit); })) {
                a[k] ^= a[rank];
            }
            if(++rank == n) {
                break;
            }
        }
        return rank;
    }
};

auto constexpr inline linera_basis = linera_basis_fn{};
using namespace std::string_literals;

auto main() -> int
{
    int n,m;
    std::cin >> m >> n;
    auto a = std::vector<std::bitset<50>>{};
    a.reserve(n);
    std::invoke([&] {
        auto cache = ""s;
        for(auto i : iota(0,n)) {
            std::cin >> cache;
            a.emplace_back(cache,0,std::string::npos,'O','X');
        }
    });
    auto rank = linera_basis.guess(a,m); // NOLINT
    auto ans = (1ULL << rank) % 2008;
    std::cout << ans;
}