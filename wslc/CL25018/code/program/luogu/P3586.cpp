

#include <bits/stdc++.h>

using i64 = long long;

struct fenwick
{

    fenwick(int n) : a(n,0) {}

    void add(int x,int val)
    {
        for(++x; x <= a.size(); x += x & -x) {
            a[x - 1] += val;
        }
    }

    i64 sum(int x)
    {
        auto ret = 0LL;
        for(; x; x -= x & -x) {
            ret += a[x - 1];
        }
        return ret;
    }

    i64 sum(int x,int y)
    { return sum(y) - sum(x); }

    std::vector<i64> a;
};

int main()
{
    auto constexpr NOTE {
        "大于 s 的数有几个" // 记录数的频率 id(数) > id(s)
        "小于 s 的数求和有几个 s" // id(数) < id(s) 把数加到id(数)上
    };
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto a = std::vector(m,std::tuple<char,int,int>{});
    for(auto& [c,x,y] : a) {
        std::cin >> c >> x >> y;
    }
    auto b = std::vector(m + 1,0);
    b[0] = 0;
    for(auto i = 0; i != m; ++i) {
        b[i + 1] = std::get<2>(a[i]);
    }
    std::ranges::sort(b);
    auto [first,end] = std::ranges::unique(b);
    b.erase(first,end);
    auto id = [&](int val) {
        return int(std::ranges::lower_bound(b,val) - b.begin());
    };
    auto nn = int(b.size());
    auto fw1 = fenwick(nn),fw2 = fenwick(nn);
    auto vec = std::vector(n,0);
    fw1.add(id(0),n);
    for(auto const& [c,x,y] : a) {
        if(c == 'U') {
            auto i = id(vec[x - 1]);
            fw1.add(i,-1);
            fw2.add(i,-vec[x - 1]);
            vec[x - 1] = y;
            i = id(vec[x - 1]);
            fw1.add(i,1);
            fw2.add(i,vec[x - 1]);
        } else {
            auto i = id(y);
            auto cnt = fw1.sum(i,nn);
            cnt += fw2.sum(i) / y;
            if(cnt < x) {
                std::cout << "NIE\n";
            } else {
                std::cout << "TAK\n";
            }
        }
    }


    return 0;
}