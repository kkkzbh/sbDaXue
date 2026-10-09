

#include <bits/stdc++.h>

using namespace std::views;

auto main() -> int
{
    auto play = std::vector {
        "zyh", "qfh", "whr","gkj","dyc","syp"
    };
    auto playtwo = std::vector {
        "zyh", "qfh", "whr","gkj","dyc","syp"
    };
    auto player = play;
    auto problems = std::vector{4, 5, 6, 7, 8, 9};
    auto easy     = std::vector{1, 2, 3};
    auto rd       = std::mt19937{ std::random_device{}() };
    auto map      = std::map<std::string, std::set<int>>{};

    for (auto i : iota(0) | take(problems.size())) {
        auto v = std::uniform_int_distribution{0, int(problems.size()) - 1}(rd);
        auto p = std::uniform_int_distribution{0, int(player.size())   - 1}(rd);
        map[player[p]].emplace(problems[v]);
        problems.erase(problems.begin() + v);
        player.erase(player.begin()     + p);
    }

    player = playtwo;
    for (auto i : iota(0) | take(easy.size())) {
        auto v = std::uniform_int_distribution{0, int(easy.size()) - 1}(rd);
        auto p = std::uniform_int_distribution{0, int(player.size()) - 1}(rd);
        map[player[p]].emplace(easy[v]);
        easy.erase(easy.begin()     + v);
        player.erase(player.begin() + p);
    }

    for (auto const& [name, prob] : map) {
        std::println("{} {}", name, prob);
    }
}
