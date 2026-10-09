

#include<bits/stdc++.h>

using namespace std::views;

struct disjoint_set
{
    explicit disjoint_set(std::integral auto n) : a(n,-1) {}

    auto find(int i) -> int
    {
        if(a[i] < 0) {
            return i;
        }
        return a[i] = find(a[i]);
    }

    auto merge(int son,int fa) -> void
    {
        auto x = find(son),y = find(fa);
        if(x == y) {
            return;
        }
        a[x] = y;
    }

    std::vector<int> a;
};

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m,s;
    std::cin >> n >> m >> s;
    --s;
    auto a = std::vector(n,std::vector<int>{});
    for(auto i : iota(1,n)) {
        int x,y;
        std::cin >> x >> y;
        --x,--y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    auto qq = std::vector(n,std::vector<std::pair<int,int>>{});
    for(auto i : iota(0,m)) {
        int x,y;
        std::cin >> x >> y;
        --x,--y;
        qq[x].emplace_back(y,i);
        qq[y].emplace_back(x,i);
    }
    auto set = disjoint_set{ n };
    auto vis = std::vector(n,false);
    auto ans = std::vector(m,0);
    auto dfs = [&](auto&& self,int it) -> void {
        vis[it] = true;
        for(auto i : a[it] | filter([&](auto i){ return not static_cast<bool>(vis[i]); })) {
            self(self,i);
            set.merge(i,it);
        }
        for(auto const& tp : qq[it] | filter([&](auto const& tp){ return static_cast<bool>(vis[std::get<0>(tp)]); })) {
            auto const& [j,index] = tp;
            ans[index] = set.find(j);
        }
    };
    dfs(dfs,s);
    for(auto v : ans) {
        std::cout << v + 1 << '\n';
    }
    std::cout << std::flush;

}