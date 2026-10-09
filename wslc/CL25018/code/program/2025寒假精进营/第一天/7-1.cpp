

import std;

using namespace std::views;

auto main() noexcept -> int
{
    std::uint32_t n;
    std::cin >> n;
    #ifndef ONLINE_JUDGE
    std::println("n的二进制表示: {:b}",n);
    #endif
    if(n == 0) {
        std::cout << 3;
        return 0;
    }
    if(n == 1) {
        std::cout << 2;
        return 0;
    }
    auto val = n;
    auto first = std::bit_floor(val);
    if(first == val) {
        std::cout << 1;
        return 0;
    }
    val -= first;
    auto second = std::bit_floor(val);
    #ifndef ONLINE_JUDGE
    std::println("first = {:b}",first);
    std::println("second = {:0{}b}",second,32 - std::countl_zero(n));
    #endif
    decltype(n) add;
    if(first == second << 1) {
        add = (first << 1 | 1) - n;
    } else {
        add = (first | (second << 1)) - n;
    }
    auto minus = n - (first | second);
    #ifndef ONLINE_JUDGE
    std::println("add = {:b}",first << 1 | 1);
    std::println("minus = {:b}",first | second);
    std::println("add = {}",add);
    std::println("minus = {}",minus);
    std::println("123456 + 7617 = {:b}",123456 + 7617);
    std::println("123456 - 7617 = {:b}",123456 - 7617);
    #endif
    std::cout << std::min(add,minus);
}