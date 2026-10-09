

#include <bits/stdc++.h>

using i64 = long long;
auto constexpr INF = std::numeric_limits<int>::max();

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto g = std::vector<std::vector<std::pair<int,int>>>(n);
    for(auto i = 1; i != n; ++i) {
        int x,y;
        std::cin >> x >> y;
        --x,--y;
        g[x].emplace_back(y,i - 1);
        g[y].emplace_back(x,i - 1);
    }
    auto dep = std::vector<int>(n);
    auto constexpr root = 0;
    auto const P = 32 - __builtin_clz(n);
    auto fa = std::vector<std::vector<int>>(n,std::vector<int>(P));
    std::function<void(int)> dfs = [&](int i) -> void {
        for(auto p = 1; p != P; ++p) {
            fa[i][p] = fa[fa[i][p - 1]][p - 1];
        }
        for(auto const& pv : g[i]) {
            auto v = pv.first;
            if(v == fa[i][0]) {
                continue;
            }
            fa[v][0] = i;
            dep[v] = dep[i] + 1;
            dfs(v);
        }
    };
    dfs(root);
    auto lca = [&](int x,int y) -> int {
        if(dep[x] < dep[y]) {
            std::swap(x,y);
        }
        for(auto p = P; p--; ) {
            auto nx = fa[x][p];
            if(dep[nx] >= dep[y]) {
                x = nx;
            }
        }
        if(x == y) {
            return x;
        }
        for(auto p = P; p--; ) {
            auto nx = fa[x][p],ny = fa[y][p];
            if(nx == ny) {
                continue;
            }
            x = nx,y = ny;
        }
        return fa[x][0];
    };
    auto dot = std::vector<int>(n);
    auto edge = std::vector<int>(n - 1);
    for(auto i = 0; i != m; ++i) {
        int x,y;
        std::cin >> x >> y;
        --x,--y;
        auto z = lca(x,y);
        ++dot[x],++dot[y];
        dot[z] -= 2;
    }
    std::function<void(int)> dfs2 = [&](int i) -> void {
        for(auto const& pv : g[i]) {
            auto v = pv.first;
            if(v == fa[i][0]) {
                continue;
            }
            dfs2(v);
        }
        for(auto const& pv : g[i]) {
            auto v = pv.first;
            auto vi = pv.second;
            if(v == fa[i][0]) {
                continue;
            }
            dot[i] += dot[v];
            edge[vi] += dot[v];
        }
    };
    dfs2(root);
    auto vec = std::vector<int>{};
    for(auto i = 0,bound = n - 1; i != bound; ++i) {
        if(edge[i] == m) {
            vec.emplace_back(i);
        }
    }
    if(vec.empty()) {
        std::cout << "-1\n";
        return 0;
    }
    std::cout << vec.back() + 1 << '\n';

}
