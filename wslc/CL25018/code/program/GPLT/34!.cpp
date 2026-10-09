

#include <iostream>
#include <bitset>
#include <string>
// #include <span>
#include <iterator>
#include <algorithm>

using namespace std::string_literals;

auto main() noexcept -> int
{
    auto s = ""s;
    std::cin >> s;
    if(s.size() == 1 and s[0] == '0') {
        std::cout << 0;
        return 0;
    }
    auto set = std::bitset<107>{ s };
    set <<= 6;
    auto num = set.to_string();
    auto i = 0;
    for(; num[i] == '0'; ++i) {

    }
    //auto span = std::span(num.begin() + i,num.end());
    std::copy(num.begin() + i,num.end(),std::ostream_iterator<char>{ std::cout,"" });
}