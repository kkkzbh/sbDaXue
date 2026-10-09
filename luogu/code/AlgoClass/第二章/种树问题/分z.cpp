

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
#define in :

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

#if __cplusplus >= 202002L
using namespace std::ranges::views;
#endif

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();

enum { luogu,codeforces,leetcode };
let constexpr check_ = luogu;

using node = std::array<int,2>; // which 0 is the mode and 1 is the cnt.

fun solve() {
    int n;
    std::cin >> n;
    let a = std::vector(n,0);
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin());
    std::ranges::sort(a);
    let divide = [&,n](this const auto& self,int l,int r) -> node {   // NOLINT
        if(l == r) {
            return { a[l],1 };
        }
        if(l + 1 == r) {
            return { a[l],1 + a[l] == a[r] };
        }
        let mid = (l + r) / 2;
        while(mid <= r and a[mid] == a[mid - 1]) {
            ++mid;
        }
        if(mid > r) {
            mid = (l + r) / 2;
            while(mid > l and a[mid] == a[mid - 1]) {
                --mid;
            }
            if(mid == l) {
                return { a[l],r - l + 1 };
            }
        }
        return std::ranges::max (
                self(l,mid - 1),self(mid,r),
                {},[](node v){ return v[1]; }
        );
    };

    std::ranges::copy(divide(0,n - 1),std::ostream_iterator<int>{ std::cout,"\n" });

}

fun main() -> signed {
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    if constexpr(check_ == codeforces) {
        let t = 0;
        std::cin >> t;
        while(t--) {
            std::invoke(solve);
        }
    } else {
        std::invoke(solve);
    }
    return 0;
}
