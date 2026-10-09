

import std;

using namespace std::views;
using namespace std::string_literals;

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    auto a = ""s;
    auto ans = 0;
    while(std::cin >> a and a != "aaa") {
        auto tot = 0;
        auto num = 0;
        for(char c : a | filter([](char c){ return std::isdigit(c); })) {
            num *= 10;
            num += c ^ 48;
            if(++tot == 2) {
                #ifndef ONLINE_JUDGE
                std::print("{} ",num);
                #endif
                tot = 0;
                ans += num;
                num = 0;
                break;
            }
        }
        #ifndef ONLINE_JUDGE
        std::println("{}",num);
        #endif
        ans += num;
    }
    std::println("{}",ans);
}