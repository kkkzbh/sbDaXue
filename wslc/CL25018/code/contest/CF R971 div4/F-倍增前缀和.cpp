

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

fun solve()
{
    int n,q;
    std::cin >> n >> q;
    let a = std::vector(n,0);
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin());
    let prefix = std::vector{ 0LL };
    for(let i in iota(0,2)) {
        for(let v in a) {
            prefix.push_back(prefix.back() + v);
        }
    }
    int64 sum = std::reduce(a.begin(),a.end(),int64{});
    while(q--) {
        int64 ans{};
        int64 l,r;
        std::cin >> l >> r;
        --l,--r;
        int pl = l / n,pr = r / n;
        l %= n,r %= n;
        ans += (pr - pl - 1LL) * sum;
        ans += prefix[pl + n] - prefix[pl + l];
        ans += prefix[1 + pr + r] - prefix[pr];
        std::cout << ans << '\n';
    }

}

fun main() -> signed
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while(t--) {
        std::invoke(solve);
    }
}