

#include <bits/stdc++.h>

struct fenwick // 标记数组的投影和
{
    using value_type = std::array<int,100>;
    using vec = std::vector<value_type>;
    using Container = std::vector<vec>;

    fenwick(int n,int m) : n(n),m(m),a(n,vec(m)) {}

    auto modify(int x,int y,int c)
    {
        for(auto i = x + 1; i <= n; i += i & -i) {
            for(auto j = y + 1; j <= m; j += j & -j) {
                a[i - 1][j - 1][c] += 1;
            }
        }
    }

    auto remove(int x,int y,int c)
    {
        for(auto i = x + 1; i <= n; i += i & -i) {
            for(auto j = y + 1; j <= m; j += j & -j) {
                a[i - 1][j - 1][c] -= 1;
            }
        }
    }

    auto sum(int x,int y,int c)
    {
        auto ret = 0;
        for(auto i = x + 1; i; i -= i & -i) {
            for(auto j = y + 1; j; j -= j & -j) {
                ret += a[i - 1][j - 1][c];
            }
        }
        return ret;
    }

    auto sum(int x1,int y1,int x2,int y2,int c)
    { return sum(x2,y2,c) - sum(x1 - 1,y2,c) - sum(x2,y1 - 1,c) + sum(x1 - 1,y1 - 1,c); }

    int n,m;
    Container a;
};

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto fw = fenwick(n,m);
    auto a = std::vector(n,std::vector(m,0));
    for(auto i = 0; i != n; ++i) {
        for(auto j = 0; j != m; ++j) {
            std::cin >> a[i][j];
            fw.modify(i,j,--a[i][j]);
        }
    }
    int q;
    std::cin >> q;
    for(auto _ = 0; _ != q; ++_) {
        int op;
        std::cin >> op;
        if(op == 1) {
            int x,y,c;
            std::cin >> x >> y >> c;
            --x,--y,--c;
            fw.remove(x,y,a[x][y]);
            a[x][y] = c;
            fw.modify(x,y,a[x][y]);
        } else {
            int x1,y1,x2,y2,c;
            std::cin >> x1 >> x2 >> y1 >> y2 >> c;
            --x1,--y1,--x2,--y2,--c;
            std::cout << fw.sum(x1,y1,x2,y2,c) << '\n';
        }
    }


    return 0;
}