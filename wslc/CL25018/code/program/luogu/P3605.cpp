

#include <bits/stdc++.h>

using i64 = long long;

struct fenwick
{
    fenwick(int n) : a(n,0) {}

    void add(int i,int val)
    {
        for(++i; i <= a.size(); i += i & -i) {
            a[i - 1] += val;
        }
    }

    i64 sum(int i)
    {
        auto ret = 0LL;
        for(; i; i -= i & -i) {
            ret += a[i - 1];
        }
        return ret;
    }

    i64 sum(int x,int y)
    { return sum(y) - sum(x); }

    std::vector<int> a;
};

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    auto a = std::vector(n,0);
    for(auto& val : a) {
        std::cin >> val;
    }
    auto g = std::vector(n,std::vector<int>{});
    for(auto i = 1; i != n; ++i) {
        int v;
        std::cin >> v;
        --v;
        g[v].emplace_back(i);
    }
    {
        auto b = a;
        std::ranges::sort(b,std::greater{});
        auto [first,end] = std::ranges::unique(b);
        b.erase(first,end);
        for(auto& val : a) {
            val = int(std::ranges::lower_bound(b,val,std::greater{}) - b.begin());
        }
    }
    auto fw = fenwick(n);
    auto ans = std::vector(n,0);
    auto dfs = [&](auto&& dfs,int i) -> void {
        auto first = fw.sum(a[i]);
        for(auto v : g[i]) {
            dfs(dfs,v);
        }
        auto end = fw.sum(a[i]);
        ans[i] = end - first;
        fw.add(a[i],1);
    };
    dfs(dfs,0);
    for(auto v : ans) {
        std::cout << v << '\n';
    }

}