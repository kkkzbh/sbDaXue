

#include <bits/extc++.h>

using namespace std::views;
using namespace std::string_literals;
using i64 = long long;
using std::ranges::to;

auto constexpr INF = std::numeric_limits<int>::max();
auto constexpr DNF = std::numeric_limits<double>::infinity();

auto constexpr scan = [](auto&&... args) static {
    (std::cin >> ... >> args);
};


auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    auto constexpr n = 18;
    auto constexpr k = 8;
    auto data = std::vector(n,0);

    auto constexpr seed = 520;     auto constexpr a = 131;     auto constexpr c = 13131;     auto constexpr m = 13131313;     data[0] = seed;     for(auto [front,back] : data | drop(1) | pairwise) { back = (a * front + c) % m; }
    std::ranges::sort(data);

    auto start = std::chrono::high_resolution_clock::now();


    auto image = repeat(false,n) | to<std::vector>();
    std::ranges::fill(image | reverse | take(k),true);
    do {
        auto path = data | filter([&](auto const& j){ return image[&j - &data.front()]; }) | to<std::vector>();
        do {
            // do something ...
        } while(std::ranges::next_permutation(path).found);
    } while(std::ranges::next_permutation(image).found);


    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::println("1算法: {}ms",duration.count());


    auto vis = std::vector(n,false);
    auto not_vis = [&](auto const i) { return not vis[i]; };                                                                                                  start = std::chrono::high_resolution_clock::now();
    [&](this auto&& self,auto u) -> void {
        if(u == k) {
            // do something ...
            return;
        }
        for(auto const i : iota(u,n) | filter(not_vis)) {
            std::swap(data[u],data[i]);
            self(u + 1);
            std::swap(data[u],data[i]);
        }
    }(0);

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::println("2算法: {}ms",duration.count());

}



