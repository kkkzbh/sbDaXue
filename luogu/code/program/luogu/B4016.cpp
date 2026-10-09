

#include<bits/stdc++.h>

auto main() -> int
{
    int n;
    std::cin >> n;
    auto a = std::vector<std::vector<int>>(n);
    for(auto i = 1; i != n; ++i) {
        int x,y;
        std::cin >> x >> y;
        --x,--y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    auto md = -1,mi = -1;
    auto dis = std::vector<int>(n,-1);
    auto dfs = [&](auto&& self,int it,int fa,int d) -> void {
        dis[it] = d;
        if(d > md) {
            mi = it;
            md = d;
        }
        for(auto i : a[it]) {
            if(i == fa) {
                continue;
            }
            self(self,i,it,d + 1);
        }
    };
    dfs(dfs,0,-1,0);
    auto l = mi;
    md = mi = -1;
    std::fill(dis.begin(),dis.end(),-1);
    dfs(dfs,l,-1,0);
    auto r = mi;
    std::cout << dis[r] << std::endl;
}