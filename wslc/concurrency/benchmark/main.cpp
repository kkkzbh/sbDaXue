

import std;

using namespace std::views;
using namespace std::chrono_literals;
#define DU   \
    std::chrono::microseconds
#define S std::ios::sync_with_stdio(false),std::cin.tie(nullptr);auto start = std::chrono::steady_clock::now();
#define E auto end = std::chrono::steady_clock::now(); std::println("bench1 = {}",std::chrono::duration_cast<DU>(end - start)); auto start2 = std::chrono::steady_clock::now();
#define E2 auto end2 = std::chrono::steady_clock::now(); std::println("bench2 = {}",std::chrono::duration_cast<DU>(end2 - start2));

auto main() -> int
{
    S

    [&] {
        for(auto i : iota(0,10)) {
            std::array<char,1000000> a{};
            (void)a;
            for(auto i : iota(0) | take(a.size())) {
                a[i] = i;
            }
            if(i == 9) {
                std::println("{}",a[4]);
            }
        }
    }();

    E

    [&] {
        for(auto j : iota(0,10)) {
            std::array<char,1000000> a;
            (void)a;
            for(auto i : iota(0) | take(a.size())) {
                a[i] = i;
            }
            if(j == 9) {
                std::println("{}",a[4]);
            }
        }
    }();

    E2
}