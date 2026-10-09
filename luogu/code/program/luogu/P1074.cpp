

#include<bits/stdc++.h>

using namespace std::views;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    auto constexpr n = 9;
    auto ss = std::vector(n,std::vector(n,0)); {
        for(auto s : iota(0,4 + 1)) {
            auto score = 6 + s;
            for(auto k : iota(s,9 - s)) {
                ss[s][k] = ss[k][8 - s] = ss[k][s] = ss[8 - s][k] = score;
            }
        }
    }
    auto hset = std::vector(n,std::set<int>{}),vset = hset,set = hset;
    auto constexpr iset = std::array {
        std::array{ 0,0,0,1,1,1,2,2,2 },
        std::array{ 0,0,0,1,1,1,2,2,2 },
        std::array{ 0,0,0,1,1,1,2,2,2 },
        std::array{ 3,3,3,4,4,4,5,5,5 },
        std::array{ 3,3,3,4,4,4,5,5,5 },
        std::array{ 3,3,3,4,4,4,5,5,5 },
        std::array{ 6,6,6,7,7,7,8,8,8 },
        std::array{ 6,6,6,7,7,7,8,8,8 },
        std::array{ 6,6,6,7,7,7,8,8,8 },
    };
    auto a = std::vector(n,std::vector(n,0)); {
        for(auto& val : a | join) {
            std::cin >> val;
        }
    }
    auto cnt = int(std::ranges::count(a | join,0));
    auto que = std::vector<std::pair<int,int>>{};
    for(auto i : iota(0,9)) {
        for(auto j : iota(0,9)) {
            if(auto const& val = a[i][j]) {
                set[iset[i][j]].insert(val);
                hset[i].insert(val);
                vset[j].insert(val);
            } else {
                que.emplace_back(i,j);
            }
        }
    }
    auto c0 = std::vector(n,0),c1 = c0; {
        for(auto i : iota(0,n)) {
            c0[i] = int(std::ranges::count(a[i],0));
            c1[i] = int(std::ranges::count(iota(0,n) | transform([&](auto j){ return a[i][j]; }),0));
        }
    }
    std::ranges::stable_sort(que,{},[&](auto const& pos) {
        auto const& [x,y] = pos;
        return c0[x];
    });
    auto insert = [&](auto const& pos,auto const val) {
        auto const& [x,y] = pos;
        set[iset[x][y]].insert(val);
        hset[x].insert(val);
        vset[y].insert(val);
    };
    auto erase = [&](auto const& pos,auto const val) {
        auto const& [x,y] = pos;
        set[iset[x][y]].erase(val);
        hset[x].erase(val);
        vset[y].erase(val);
    };
    auto contains = [&](auto const& pos,auto const val) {
        auto const& [x,y] = pos;
        return  vset[y].contains(val) or hset[x].contains(val) or set[iset[x][y]].contains(val);
    };
    auto ans = -1;
    auto dfs = [&,ct = 0](auto&& self,auto p) mutable -> void {
        if(++ct >= 2e6 + 8e5 + 5e4 + 2e3) {
            return;
        }
        if(cnt == 0) {
            decltype(ans) tmp = 0;
            for(auto i : iota(0,9)) {
                for(auto j : iota(0,9)) {
                    tmp += ss[i][j] * a[i][j];
                }
            }
            ans = std::max(ans,tmp);
            return;
        }
        auto const& pos = que[p];
        auto const& [x,y] = pos;
        auto constexpr debug = false; // NOLINT
        for(auto i : iota(1,9 + 1) | reverse | filter([&](auto i){ return not contains(pos,i); })) {

            if constexpr(debug) {
                for(auto i : iota(0,9)) {
                    for(auto j : iota(0,9)) {
                        if(i == x and j == y) {
                            std::cout << std::format("|{}| ",a[i][j]);
                        } else {
                            std::cout << a[i][j] << ' ';
                        }
                    }
                    std::cout << '\n';
                }
                std::cout << std::format("x = {},y = {}, cnt = {}\n",x,y,cnt);
                std::cout << '\n';
            }

            insert(pos,i);
            a[x][y] = i;
            --cnt;
            self(self,p + 1);
            ++cnt;
            a[x][y] = 0;
            erase(pos,i);

            if constexpr(debug) {
                for(auto i : iota(0,9)) {
                    for(auto j : iota(0,9)) {
                        if(i == x and j == y) {
                            std::cout << std::format("|{}| ",a[i][j]);
                        } else {
                            std::cout << a[i][j] << ' ';
                        }
                    }
                    std::cout << '\n';
                }
                std::cout << std::format("x = {},y = {}, cnt = {}\n",x,y,cnt);
                std::cout << '\n';
            }

        }
    };
    dfs(dfs,0);
    std::cout << ans;

}