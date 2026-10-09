

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

enum { luogu,codeforces };
let constexpr check_ = codeforces;

fun solve()
{
    int n,k;
    std::cin >> n >> k;
    let a = std::vector(n,0);
    for(let &v in a) {
        std::cin >> v;
    }
    if(n == 1) {
        if(k - 1 < a[0]) {
            std::cout << k - 1 << '\n';
        } else {
            std::cout << k << '\n';
        }
        return;
    }
    let g = std::ranges::fold_left(a,0,std::gcd<int,int>);
    if(!g) {
        std::cout << k << '\n';
        return;
    }
    a[0] = 0;
    for(let i in iota(1,int(a.size()))) {
        a[i] = a[i - 1] + g;
    }
    if(g == 1) {
        std::cout << a.back() + k << '\n';
        return;
    }
    let m = k % (g - 1);
    let it = k / (g - 1);
    if(it >= 0 and it < a.size()) {
        if(m) {
            std::cout << a[it] + m << '\n';
        } else {
            std::cout << a[it] - 1 << '\n';
        }
    } else {
        k -= (int(a.size()) - 1) * (g - 1);
        std::cout << a.back() + k << '\n';
    }

}

fun main() -> signed
{
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