

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
    return 1LL * (x.x - y.x) * (x.x - y.x) +
           1LL * (x.y - y.y) * (x.y - y.y);
}

fun solve()
{
    int n;
    std::cin >> n;
    std::vector<point> a(n);
    for(auto& [x,y] : a) {
        std::cin >> x >> y;
    }
    int64 ans{ INF64 };
    for(int i : iota(0,n - 1)) {
        for(int j : iota(i + 1,n)) {
            ans = std::min(distance2(a[i],a[j]),ans);
        }
    }
    std::cout << std::format("{:.4f}",std::sqrt(ans));
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}