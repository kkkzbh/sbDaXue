

import std;

using namespace std::string_literals;

auto decl(std::span<char> s) noexcept -> char // 可以改用前缀和优化 利用区间和判断
{
    if(std::ranges::all_of(s,[](char c){ return c == '0'; })) {
        return 'B';
    }
    if(std::ranges::all_of(s,[](char c){ return c == '1'; })) {
        return 'I';
    }
    return 'F';
}

auto back(std::span<char> s) noexcept -> void
{
    auto mid = s.size() / 2;
    if(s.size() == 1) {
        std::cout << decl(s);
        return;
    }
    back(s.first(mid));
    back(s.last(mid));
    std::cout << decl(s);
}

auto main() noexcept -> int
{
    int n;
    auto s = ""s;
    std::cin >> n >> s;
    back(s);
}