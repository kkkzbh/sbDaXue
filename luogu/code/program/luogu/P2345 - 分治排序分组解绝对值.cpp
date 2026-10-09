

#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<numeric>
#include<cstring>
#include<functional>
#include<string>
#include<bitset>
#include<deque>
#include<queue>
#include<cassert>
#include<stack>
#include<optional>
#include<array>
#include<unordered_set>
#include<unordered_map>
#include<map>
#include<set>
#include<fstream>


#if __cplusplus >= 202002L
#include<format>
#include<ranges>
#include<bit>
#include<span>
#endif

#define fun auto
#define let auto

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

#if __cplusplus >= 202002L
using namespace std::ranges::views;
#endif

constexpr int INF = std::numeric_limits<int>::max();
constexpr int64 INF64 = std::numeric_limits<int64>::max();

struct node
{
    int v,x;
};

fun solve()
{
    int n;
    std::cin >> n;
    let a = std::vector(n,node{});
    for(auto& [v,x] : a) {
        std::cin >> v >> x;
    }
    std::ranges::sort(a,{},[](node i){ return i.v; });
    let merge = [f = [&](auto& self,int l,int r) {
        if(r - l == 1) {
            return 0LL;
        }
        int mid = (l + r) / 2;
        int64 res = self(self,l,mid) + self(self,mid,r);
        int lv{},rv{};
        for(int i : iota(l,mid)) {
            rv += a[i].x;
        }
        let tmp = std::vector<node>{};
        int it{ l };
        for(int i : iota(mid,r)) {
            while(it != mid and a[i].x > a[it].x) {
                lv += a[it].x;
                rv -= a[it].x;
                tmp.push_back(a[it++]);
            }
            tmp.push_back(a[i]);
            res += (1LL * (it - l) * a[i].x - lv) * a[i].v + (rv - 1LL * (mid - it) * a[i].x) * a[i].v;
        }
        while(it != mid) {
            tmp.push_back(a[it++]);
        }
        std::ranges::copy(tmp,a.begin() + l);
        return res;

    }](int l,int r){ return f(f,l,r); };

    let ans = merge(0,n);
    std::cout << ans;

}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}