

#include <bits/stdc++.h>

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto a = std::vector(n,0),b = std::vector(m,0);
    for(auto& v : a) {
        std::cin >> v;
    }
    for(auto& v : b) {
        std::cin >> v;
    }
    if(a[0] != b[0]) {
        std::cout << "0\n";
        return 0;
    }
    auto ga = std::vector(n,std::vector<int>{});
    auto gb = std::vector(m,std::vector<int>{});
    for(auto i = 1; i != n; ++i) {
        int u,v;
        std::cin >> u >> v;
        --u,--v;
        ga[u].emplace_back(v);
        ga[v].emplace_back(u);
    }
    for(auto i = 1; i != m; ++i) {
        int u,v;
        std::cin >> u >> v;
        --u,--v;
        gb[u].emplace_back(v);
        gb[v].emplace_back(u);
    }

    // auto set = std::vector<std::set<int>>{};
    auto set = std::map<int,std::set<int>>{};
    auto que = std::deque<int>{};
    que.emplace_back(0);
    auto h = 0;
    auto vis = std::vector(m,false);
    vis[0] = true;
    while(not que.empty()) {
        for(auto i = 0,bound = int(que.size()); i != bound; ++i) {
            auto it = que.front();
            que.pop_front();
            for(auto v : gb[it]) {
                if(vis[v]) {
                    continue;
                }
                set[b[it]].emplace(b[v]);
                que.emplace_back(v);
                vis[v] = true;
            }
        }
        ++h;
    }
    h = 0;
    vis.assign(n,false);
    que.emplace_back(0);
    vis[0] = true;
    while(not que.empty()) {
        for(auto i = 0,bound = int(que.size()); i != bound; ++i) {
            auto it = que.front();
            que.pop_front();
            for(auto v : ga[it]) {
                if(vis[v] or not set[a[it]].count(a[v])) {
                    continue;
                }
                que.emplace_back(v);
                vis[v] = true;
            }
        }
        ++h;
    }

    std::cout << h << '\n';

}