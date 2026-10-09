

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

struct point
{
    int x,y;
};

fun distance2(point x,point y) -> int64
{
    int64 dx = x.x - y.x;
    int64 dy = x.y - y.y;
    return dx * dx + dy * dy;
}

fun solve()
{
    int n;
    std::cin >> n;
    std::vector a(n,point{});
    for(auto& [x,y] : a) {
        std::cin >> x >> y;
    }
    std::ranges::sort(a,std::less<>{},[](point p){ return p.x; });

    let merge = [f = [&](auto& self,int l,int r) {
        if(r - l == 3) {
            return std::sqrt(std::ranges::min ({
                                                       distance2(a[l],a[l + 1]),
                                                       distance2(a[l + 1],a[l + 2]),
                                                       distance2(a[l],a[l + 2])
                                               }));
        }
        if(r - l == 2) {
            return std::sqrt(distance2(a[l],a[l + 1]));
        }
        int mid = (l + r) / 2;
        double res = std::min(self(self,l,mid),self(self,mid,r));
        std::vector<int> x,y;
        for(int i : iota(l,mid) | reverse | take_while([&,mid,res](int i){ return a[mid].x - a[i].x <= res; })) {
            x.push_back(i);
        }
        y.push_back(mid);
        for(int i : iota(mid + 1,r) | take_while([&,mid,res](int i) { return a[i].x - a[mid].x <= res; })) {
            y.push_back(i);
        }
        let trans = transform([&](int i){ return a[i]; });
        for(point left : x | trans) {
            for(point right : y | trans) {
                res = std::min(res,std::sqrt(distance2(left,right)));
            }
        }
        return res;

    }](int l,int r) { return f(f,l, r); };
    double ans = merge(0,n);
    std::cout << std::format("{:.4f}",ans);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}