

import std;

using namespace std::views;
using namespace std::string_literals;
using namespace std::string_view_literals;

auto main() noexcept -> int
{
    int n;
    std::cin >> n;
    auto ss = std::vector(n,""s);
    for(auto& s : ss) {
        std::cin >> s;
    }
    int k;
    std::cin >> k;
    auto word = ""s;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::getline(std::cin,word);
    auto censored = "@~"sv;
    auto tot = censored.size();
    auto cnt = 0;
    std::invoke([&] noexcept {
        for(auto const& s : ss) {
            if(s == censored) {
                continue;
            }
            auto sz = s.size();
            for(auto it = word.find(s); it != -1; it = word.find(s,it + tot) ) {
                word.replace(it,sz,censored);
                ++cnt;
            }
        }
    });
    if(cnt >= k) {
        std::println("{}",cnt);
        std::println("He Xie Ni Quan Jia!");
        return 0;
    }
    auto rep = "<censored>"sv;
    for(auto it = word.find(censored); it != -1; it = word.find(censored,it + rep.size())) {
        word.replace(it,tot,rep);
    }
    std::println("{}",word);
}