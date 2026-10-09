#include<bits/extc++.h>

#define fun auto
#define let auto
#define in :

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

using namespace std;

namespace gnu
{
    using namespace __gnu_pbds;
    using namespace __gnu_cxx;
}

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();


class Solution {
public:
    int longestCommonSubsequence(string a, string b) {

        let n = int(a.size());
        let m = int(b.size());
        let dp = std::vector(m + 1,0);

        for(let i in std::views::iota(1,n + 1)) {
            let k = dp[0];
            for(let j in std::views::iota(1,m + 1)) {
                let _ = dp[j];
                if(a[i - 1] == b[j - 1]) {
                    dp[j] = k + 1;
                } else {
                    dp[j] = std::ranges::max(dp[j],dp[j - 1]);
                }
                k = _;
            }
        }

        return dp[m];
    }
};