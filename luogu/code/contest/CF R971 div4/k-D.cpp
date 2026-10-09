

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

struct point
{
    fun friend operator<=>(point l,point r)
    { return l.x == r.x ? l.y <=> r.y : l.x <=> r.x; }
    int x,y;
};

fun solve()
{
    int n;
    std::cin >> n;
    std::set<point> set,s;
    for(int i : iota(0,n)) {
        int x,y;
        std::cin >> x >> y;
        set.emplace(x,y);
    }
    int64 ans{};
    for(let [x,y] : set) {
        let it1 = set.find(point{ x,y ^ 1 });
        if(it1 != set.end() and !s.contains(point{ x,y })) {
            s.emplace(x,y ^ 1);
            ans += n - 2;
        }
        if(set.contains(point{ x - 1,y ^ 1 }) and set.contains(point{ x + 1,y ^ 1 })) {
            ++ans;
        }
    }
    std::cout << ans << '\n';
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while(t--) {
        std::invoke(solve);
    }
}