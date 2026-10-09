

import std;

auto main() noexcept -> int
{
    int a,b;
    std::cin >> a >> b;
    a += b;
    auto s = std::format("{}",a);
    auto n = static_cast<int>(s.size());
    auto stk = std::vector<char>{};
    auto start = static_cast<int>(s[0] == '-');
    for(auto tot = 0; auto c : s | std::views::drop(start) | std::views::reverse) {
        stk.push_back(c);
        if(++tot == 3) {
            stk.push_back(',');
            tot = 0;
        }
    }
    if(start) {
        std::cout << '-';
    }
    std::ranges::copy(stk | std::views::reverse,std::ostream_iterator<char>{ std::cout,"" });
}