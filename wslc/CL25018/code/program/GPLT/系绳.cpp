

#include <bits/stdc++.h>

struct disjoint_set
{

    explicit disjoint_set(int n) : a(n,-1),edge(n,0) {}

    auto root(int i) -> bool
    { return a[i] < 0; }

    auto find(int i) -> int
    {
        if(root(i)) {
            return i;
        }
        return a[i] = find(a[i]);
    }

    auto merge(int x,int y)
    {
        auto fx = find(x),fy = find(y);
        if(fx == fy) {
            ++edge[fx];
            return;
        }
        a[fy] += a[fx];
        a[fx] = fy;
        edge[fy] += edge[fx] + 1;
    }

    auto count(int i) -> int
    { return -a[find(i)]; }

    auto circle(int i) -> bool
    { return count(i) == edge[find(i)]; }

    std::vector<int> a,edge;
};

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m; // 红与蓝
    auto set = disjoint_set(2 * n);
    auto map = std::map<char,int>{
            { 'R',0 },
            { 'B',1 }
    };
    for(auto i = 0; i != n; ++i) {
        auto i2 = 2 * i;
        set.merge(i2,i2 + 1);
    }
    for(auto i = 0; i != m; ++i) {
        int x,y;
        char cx,cy;
        std::cin >> x >> cx >> y >> cy;
        --x,--y;
        set.merge(2 * x + map[cx],2 * y + map[cy]);
    }
    auto X = 0,Y = 0;
    for(auto i = 0,bound = 2 * n; i != bound; ++i) {
        if(not set.root(i)) {
            continue;
        }
        if(set.circle(i)) {
            ++X;
        } else {
            ++Y;
        }
    }
    std::cout << X << ' ' << Y;

}


