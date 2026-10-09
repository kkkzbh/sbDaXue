

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

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();

// 3 4 5 6 7

fun solve()
{
    int n,k;
    std::cin >> n >> k;
    let val = [n,k](int i) {
        return (0LL + k + k + i) * (i + 1LL) / 2LL - (k + i + 1LL + k + n - 1LL) * (n - 1LL - i) / 2LL;
    };
    int l{ 1 },r{ n - 1 };
    while(l != r) {
        int mid = (l + r) / 2;
        if(val(mid) >= 0) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    int64 a = -val(l - 1),b = val(l);
    std::cout << std::min(a,b) << '\n';

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