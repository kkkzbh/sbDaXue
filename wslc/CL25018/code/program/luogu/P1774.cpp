

#include <bits/stdc++.h>

#define r(C) C.begin(),C.end()

using int64 = long long;

struct fenwick
{
    explicit fenwick(int n) : a(n,0) {}

    void add(int i,int val)
    {
        for(++i; i <= a.size(); i += i & -i) {
            a[i - 1] += val;
        }
    }

    int64 sum(int i)
    {
        auto ret = 0LL;
        for(; i; i -= i & -i) {
            ret += a[i - 1];
        }
        return ret;
    }

    int64 sum(int x,int y)
    { return sum(y) - sum(x); }

    std::vector<int> a;
};

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    auto a = std::vector<int>(n,0);
    for(auto& val : a) {
        std::cin >> val;
    }
    auto b = a;
    {
        std::sort(b.begin(),b.end(),std::greater<int>{});
        auto it = std::unique(b.begin(),b.end());
        b.erase(it,b.end());
    }
    auto id = [&](int val) {
        return int(std::lower_bound(r(b),val,std::greater<int>{}) - b.begin());
    };
    auto ans = 0LL;
    auto fw = fenwick{ n };
    for(auto val : a) {
        auto i = id(val);
        ans += fw.sum(i);
        fw.add(i,1);
    }
    std::cout << ans << '\n';

}