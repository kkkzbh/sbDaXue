

#include<bits/stdc++.h>

#define fun auto
#define let auto
#define in :

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

using namespace std::ranges::views;

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();


fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    let a = std::vector(n,0);
    for(let &v in a) {
        std::cin >> v;
    }
    let sum = std::reduce(a.begin(),a.end());
    let v = sum / 2;

    let dp = std::vector(v + 1,0);

    for(let i in iota(0,n)) {
        for(let j in iota(a[i],v + 1) | reverse) {
            dp[j] = std::max(dp[j],dp[j - a[i]] + a[i]);
        }
    }

    std::cout << dp[v];

    return 0;
}


