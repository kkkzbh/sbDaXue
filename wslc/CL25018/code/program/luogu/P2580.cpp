

#include<bits/stdc++.h>

auto constexpr ans = std::array {
    "OK","REPEAT","WRONG"
};

struct trie
{
    auto static constexpr size = 640000;
    auto static constexpr root = 0,null = 0;
    using dict = std::array<int,26>;

    auto static map(auto c) -> int
    { return c ^ 96; }

    auto insert(std::string_view s) -> void
    {
        auto it = root;
        for(auto c : s) {
            auto& next = a[it];
            auto mc = map(c);
            if(next[mc] == null) {
                next[mc] = tot++;
            }
            it = next[mc];
        }
        ++num[it];
    }

    auto find(std::string_view s) -> int
    {
        auto it = root;
        for(auto c : s) {
            auto& next = a[it];
            auto mc = map(c);
            if(next[mc] == null) {
                return 2;
            }
            it = next[mc];
        }
        if(num[it] == false) {
            return 2;
        }
        if(not repeat[it]) {
            repeat[it] = true;
            return 0;
        }
        return 1;
    }

    int tot = 1;
    std::array<dict,size> a;
    std::array<int,size> num;
    std::array<bool,size> repeat;
};


auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    auto tr = trie{};
    using namespace std::string_literals;
    auto s = ""s;
    using namespace std::views;
    for(auto i : iota(0,n)) {
        std::cin >> s;
        tr.insert(s);
    }
    int m;
    std::cin >> m;
    for(auto i : iota(0,m)) {
        std::cin >> s;
        std::cout << ans[tr.find(s)] << '\n';
    }


}