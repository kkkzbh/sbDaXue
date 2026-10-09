

#include <bits/stdc++.h>

using i64 = long long;
auto constexpr INF = std::numeric_limits<int>::max();

struct segment
{

    auto merge(int i) -> void
    {
        auto l = left(i),r = right(i);
        (sum_data[i] = sum_data[l] + sum_data[r]) %= MOD;
    }

    explicit segment(std::vector<int> const& a,std::vector<int> const& index,int& p) :
    n(a.size()),sum_data(4 * n),add_lazy(4 * n),MOD(p)
    {
        std::function<void(int,int,int)> build = [&](int i,int il,int ir) -> void {
            if(ir - il == 1) {
                sum_data[i] = a[index[il]] % MOD;
                return;
            }
            auto mid = (il + ir) / 2;
            build(left(i),il,mid);
            build(right(i),mid,ir);
            merge(i);
        };
        build(0,0,n);
    }

    auto lazy(int i,int sz,i64 v) -> void
    {
        (sum_data[i] += sz * v) %= MOD;
        (add_lazy[i] += v) %= MOD;
    }

    auto down(int i,int sz) -> void
    {
        lazy(left(i),sz / 2,add_lazy[i]);
        lazy(right(i),sz - sz / 2,add_lazy[i]);
        add_lazy[i] = 0;
    }

    auto add(int l,int r,int v) -> void
    {
        std::function<void(int,int,int)> add = [&](int i,int il,int ir) -> void {
            if(il >= l and ir <= r) {
                lazy(i,ir - il,v);
                return;
            }
            down(i,ir - il);
            auto mid = (il + ir) / 2;
            if(l < mid) {
                add(left(i),il,mid);
            }
            if(r > mid) {
                add(right(i),mid,ir);
            }
            merge(i);
        };
        add(0,0,n);
    }

    auto sum(int l,int r) -> i64
    {
        std::function<i64(int,int,int)> sum = [&](int i,int il,int ir) -> i64 {
            if(il >= l and ir <= r) {
                return sum_data[i];
            }
            down(i,ir - il);
            auto s = 0LL;
            auto mid = (il + ir) / 2;
            if(l < mid) {
                s += sum(left(i),il,mid);
            }
            if(r > mid) {
                s += sum(right(i),mid,ir);
            }
            return s % MOD;
        };
        return sum(0,0,n);
    }

    int n;
    int& MOD;
    std::vector<i64> sum_data;
    std::vector<i64> add_lazy;

    auto static left(int i) -> int
    { return i * 2 + 1; }

    auto static right(int i) -> int
    { return left(i) + 1; }
};

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m,r,p;
    std::cin >> n >> m >> r >> p;
    --r;
    auto a = std::vector<int>(n);
    for(auto& v : a) {
        std::cin >> v;
    }
    auto g = std::vector<std::vector<int>>(n);
    for(auto i = 1; i != n; ++i) {
        int x,y;
        std::cin >> x >> y;
        --x,--y;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    auto fa = std::vector<int>(n);
    auto dfn = std::vector<int>(n);
    auto size = std::vector<int>(n,1);
    auto top = std::vector<int>(n);
    auto index = std::vector<int>(n);
    auto son = std::vector<int>(n,-1);
    auto dep = std::vector<int>(n);
    auto ct = 0;
    fa[r] = r;
    std::function<void(int)> dfs1 = [&](int i) -> void {
        for(auto v : g[i]) {
            if(v == fa[i]) {
                continue;
            }
            fa[v] = i;
            dep[v] = dep[i] + 1;
            dfs1(v);
            size[i] += size[v];
            if(son[i] == -1 or size[son[i]] < size[v]) {
                son[i] = v;
            }
        }
    };
    dfs1(r);
    std::function<void(int,int)> dfs2 = [&](int i,int t) -> void {
        top[i] = t;
        index[ct] = i;
        dfn[i] = ct++; // *************** 修改了ct ！
        if(son[i] == -1) {
            return;
        }
        dfs2(son[i],t);
        for(auto v : g[i]) {
            if(v == son[i] or v == fa[i]) {
                continue;
            }
            dfs2(v,v);
        }
    };
    dfs2(r,r);
    auto seg = segment{ a,index,p };

    auto path_add = [&](int x,int y,int v) -> void {
        while(top[x] != top[y]) {
            if(dep[top[x]] < dep[top[y]]) {
                std::swap(x,y);
            }
            seg.add(dfn[top[x]],dfn[x] + 1,v);
            x = fa[top[x]];
        }
        auto mm = std::minmax(dfn[x],dfn[y]);
        seg.add(mm.first,mm.second + 1,v);
    };

    auto path_print = [&](int x,int y) -> i64 {
        auto ans = 0LL;
        while(top[x] != top[y]) {
            if(dep[top[x]] < dep[top[y]]) {
                std::swap(x,y);
            }
            (ans += seg.sum(dfn[top[x]],dfn[x] + 1)) %= p;
            x = fa[top[x]];
        }
        auto mm = std::minmax(dfn[x],dfn[y]);
        return (ans + seg.sum(mm.first,mm.second + 1)) % p;
    };

    auto subtree_add = [&](int x,int v) -> void {
        seg.add(dfn[x],dfn[x] + size[x],v);
    };

    auto subtree_print = [&](int x) -> i64 {
        return seg.sum(dfn[x],dfn[x] + size[x]);
    };

    for(auto i = m; i--; ) {
        int op;
        std::cin >> op;
        if(op == 1) {
            int x,y,z;
            std::cin >> x >> y >> z;
            --x,--y;
            path_add(x,y,z);
        } else if(op == 2) {
            int x,y;
            std::cin >> x >> y;
            --x,--y;
            std::cout << path_print(x,y) << '\n';
        } else if(op == 3) {
            int x,z;
            std::cin >> x >> z;
            --x;
            subtree_add(x,z);
        } else if(op == 4) {
            int x;
            std::cin >> x;
            --x;
            std::cout << subtree_print(x) << '\n';
        }
    }
}
