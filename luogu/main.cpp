

#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>

using namespace std::views;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto a = std::vector(n,std::vector(m,0));
    for(auto& val : a | join) {
        std::cin >> val;
    }
    auto que = std::invoke([&]{
        auto que_cmp = [&,cmp = std::less{},proj = [&](auto i){ return a[0][i]; }](auto li,auto ri) {
            return std::invoke(cmp,std::invoke(proj,li),std::invoke(proj,ri));
        };
        using que_t = __gnu_pbds::priority_queue<int,decltype(que_cmp)>;
        return que_t{ que_cmp };
    });
    for(auto i : iota(0,m)) {
        que.push(i);
    }

    auto constexpr move = std::array{ -1,0,1,0,-1 };


    auto v = std::vector(n,std::vector(m,false));

    auto ok = [&](auto x,auto y,auto mx,auto my) {
        return mx >= 0 and mx < n and my >= 0 and my < m and not v[mx][my] and a[x][y] > a[mx][my];
    };

    auto dfs = [&](auto&& self,int sx,int sy) -> void {
        if(sx == 0 or sx == n - 1) {
            v[sx][sy] = true;
        }
        for(auto i : iota(0,4)) {
            if(auto mx = sx + move[i],my = sy + move[i + 1]; ok(sx,sy,mx,my)) {
                self(self,mx,my);
            }
        }
    };

    auto cnt = 0;

    for(auto i : iota(0,m)) {
        auto ci = que.top();
        que.pop();
        if(not v[0][ci] and std::ranges::any_of(v[n - 1],[](auto flag){ return flag == 0; })) {
            ++cnt;
            dfs(dfs,0,ci);
        }
    }

    if(std::ranges::all_of(v[n - 1],[](auto flag){ return flag; })) {
        std::cout << std::format("1\n{}",cnt);
    } else {
        std::cout << std::format("0\n{}",std::ranges::count(v[n - 1],0));
    }

    return 0;
}
