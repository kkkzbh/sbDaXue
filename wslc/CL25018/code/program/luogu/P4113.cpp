

#include <bits/stdc++.h>

using i64 = long long;

struct fenwick
{
    using value_type = int;
    using container = std::vector<value_type>;

    fenwick(int n) : a(n) {}

    int static lowbit(int x)
    { return x & -x; }

    void add(int i,int val)
    {
        for(++i; i <= a.size(); i += lowbit(i)) {
            a[i - 1] += val;
        }
    }

    int sum(int i)
    {
        auto ret = 0;
        for(; i; i -= lowbit(i)) {
            ret += a[i - 1];
        }
        return ret;
    }

    int sum(int x,int y)
    { return sum(y) - sum(x); }

    container a;
};

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,c,m;
    std::cin >> n >> c >> m;
    auto a = std::vector(n,0);
    for(auto& val : a) {
        std::cin >> val;
    }
    auto q = std::vector(m,std::pair<int,int>{});
    for(auto& [l,r] : q) {
        std::cin >> l >> r;
        --l,--r;
    }
    auto iq = std::vector(m,0);
    for(auto i = 0; i != m; ++i) {
        iq[i] = i;
    }
    std::ranges::sort(iq,{},[&](auto i){ return std::get<1>(q[i]); });
    auto map = std::unordered_map<int,int>{};
    auto map2 = std::unordered_map<int,int>{};
    auto ans = std::vector(m,0);
    auto it = 0;
    auto fw = fenwick(n);
    for(auto i : iq) {
        auto const& [l,r] = q[i];
        for(; it <= r; ++it) {
            if(map.contains(a[it])) {
                if(map2.contains(a[it])) {
                    fw.add(map2[a[it]],-1);
                }
                auto& val = map[a[it]];
                map2[a[it]] = val;
                fw.add(val,1);
            }
            map[a[it]] = it;
        }
        ans[i] = fw.sum(l,r + 1);
    }
    for(auto v : ans) {
        std::cout << v << '\n';
    }


    return 0;
}