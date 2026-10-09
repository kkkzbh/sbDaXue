

#include<bits/stdc++.h>

struct pam
{
    auto static constexpr MAX_SIZE = 640000;
    using dict = std::array<int,26>;

    auto get_fail(int p) -> int
    {
        auto it = int(s.size()) - 1;
        while(it - size[p] - 1 < 0 or s[it - size[p] - 1] != s.back()) {
            p = fail[p];
        }
        return p;
    }

    auto static map(char c) -> int
    { return c - 'a'; }

    auto push_back(char c)
    {
        s.push_back(c);
        auto it = get_fail(last);
        auto mc = map(c);
        if(not next[it][mc]) {
            size.emplace_back(size[it] + 2);
            fail.emplace_back(next[get_fail(fail[it])][mc]);
            cnt.emplace_back(cnt[fail[tot]] + 1);
            next.emplace_back();
            next[it][mc] = tot++;
        }
        last = next[it][mc];
        return cnt[last];
    }

    std::vector<int> size{ 0,-1 };
    std::vector<int> cnt{ 0,0 };
    std::vector<int> fail{ 1,1 };
    std::vector<dict> next{ {},{} };
    std::string s;
    int tot = 2;
    int last = 0;
};

using namespace std::string_literals;
using namespace std::views;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    auto s = ""s;
    std::cin >> s;
    auto p = pam{};
    auto ans = p.push_back(s.front());
    std::cout << ans << ' ';

    for(auto c : s | drop(1)) {
        auto cc = ((c - 97 + ans) % 26) + 97;
        ans = p.push_back(cc);
        std::cout << ans << ' ';
    }

}