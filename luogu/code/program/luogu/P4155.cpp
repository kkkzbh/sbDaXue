

#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<ranges>

#define fun auto
#define main int main

using int64 = long long;
using namespace std::ranges::views;

constexpr int null = -1;

struct node
{
    fun friend operator>>(std::istream& is,node& n) -> std::istream&
    {
        return is >> n.l >> n.r;
    }
    int l,r;
    int id;
};

// 倍增是一种思想, 而st表求区间可重复贡献问题 属于倍增一类,倍增思想常用st表模拟实现 本题 倍增 + 贪心 + 二分

main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    std::vector<node> a(n << 1);
    for(int i{}; i != n; ++i) { // init
        std::cin >> a[i];
        --a[i].l,--a[i].r;
        if(a[i].r < a[i].l) {
            a[i].r += m;
        }
        a[i].id = i;
    }
    std::ranges::sort(a | take(n),[](node x,node y){ return x.l < y.l; });
    for(int i{}; i != n; ++i) {
        a[i + n] = { a[i].l + m,a[i].r + m,a[i].id };
    }
    int n2{ n << 1 };
    int lgn = log2(n);
    std::vector<std::vector<int>> st(n2,std::vector<int>(lgn + 1,null));
    for(int i{},it{}; i != n2; ++i) {
        while(it + 1 != n2 and a[it + 1].l <= a[i].r) {
            ++it;
        }
        st[i][0] = it;
    }
    for(int p{ 1 }; p <= lgn; ++p) {
        for(int i{}; i != n2; ++i) {
            st[i][p] = st[st[i][p - 1]][p - 1];
        }
    }
    std::vector<int> ans(n);
    auto jump = [&,m,lgn](int i) {
        int ret{ 1 };
        int r{ a[i].l + m };
        for(int p{ lgn }; p >= 0; --p) {
            int to{ st[i][p] };
            if(a[to].r < r) {
                ret += 1 << p;
                i = to;
            }
        }
        return ret + 1;
    };
    for(int i{}; i != n; ++i) {
        ans[a[i].id] = jump(i);
    }
    for(int i{}; i != n; ++i) {
        std::cout << ans[i] << ' ';
    }

    return 0;
}