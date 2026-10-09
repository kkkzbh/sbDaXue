

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
    using namespace std::views;
    let scan = []<typename... T>(T&... vs) { (std::cin >> ... >> vs); };

    int n;
    std::cin >> n;
    let a = std::vector(n,0),b = a;
    std::ranges::for_each(a,scan);
    std::ranges::for_each(b,scan);

    // dp[i][A] = min -> dp[i][A - u] or dp[i - 1][A] + u
    let sumA = std::reduce(a.begin(),a.end());
    let sumB = std::reduce(b.begin(),b.end());
    if(sumA > sumB) {
        std::swap(a,b);
        std::swap(sumA,sumB);
    }

    #define sum sumA

    let constexpr bound = 1147483647;
    let dp = std::vector(n + 1,std::vector(sum + 1,bound));
    dp[0][0] = 0;

    for(let i in iota(1,n + 1)) {
        for(let j in iota(0,a[i - 1])) {
            dp[i][j] = std::min(dp[i - 1][j] + b[i - 1],bound);
        }
        for(let j in iota(a[i - 1],sum + 1)) {
            dp[i][j] = std::min({ dp[i - 1][j - a[i - 1]],dp[i - 1][j] + b[i - 1],bound });
        }
    }

    let const& v = dp[n];
    let ans = 2147483647;
    for(let j in iota(0,sum + 1) | filter([&](int j){ return v[j] != bound; })) {
        ans = std::min(ans,std::max(j,v[j]));
    }
    std::cout << ans;


    return 0;
}


