

import std;
#include <alloca.h>

using namespace std::views;
using namespace std::string_literals;

auto main() noexcept -> int
{
    int n;
    std::cin >> n;
    auto s = ""s;
    std::cin >> s;
    auto it = s.find("flag");
    it += 4;
    auto num = s[it] ^ 48;
    num *= 10;
    num += s[it + 1] ^ 48;
    it += 2;
    auto flag = std::span(s.begin() + it,num);
    std::print("flag{{");
    for(char c : flag) {
        std::print("{}",c);
    }
    std::print("}}");
}