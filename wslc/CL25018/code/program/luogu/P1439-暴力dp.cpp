

#include<bits/extc++.h>

#define fun auto
#define let auto
#define in :

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

using namespace std::ranges::views;

namespace gnu
{
    using namespace __gnu_pbds;
    using namespace __gnu_cxx;
}

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();


fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    let a = std::vector(n,0),b = a;
    for(let &v in a) {
        std::cin >> v;
    }
    for(let &v in b) {
        std::cin >> v;
    }

    let dp = std::vector(n + 1,0);

    for(let i in iota(1,n + 1)) {
        let k = dp[0];
        for(let j in iota(1,n + 1)) {
            let _ = dp[j];
            if(a[i - 1] == b[j - 1]) {
                dp[j] = k + 1;
            } else {
                dp[j] = std::ranges::max(dp[j],dp[j - 1]);
            }
            k = _;
        }
    }

    std::cout << dp[n];

    return 0;
}


