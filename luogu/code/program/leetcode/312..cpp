

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

using namespace std;

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();

enum { luogu,codeforces,leetcode };
let constexpr check_ = codeforces;

namespace sv = std::views;

class Solution {
public:
    int static maxCoins(vector<int>& a) {

        a.insert(a.begin(),1);
        a.push_back(1);

        let dp = std::vector(a.size(),std::vector(a.size(),0));
        let bound = int(a.size()) - 1;
        for(let i in sv::iota(1,bound) | sv::reverse) {
            for(let j in sv::iota(i,bound)) {
                dp[i][j] = std::ranges::max (
                        sv::iota(i,j + 1) | sv::transform([&,i,j](int k) {
                            return a[k] * a[i - 1] * a[j + 1] + dp[i][k - 1] + dp[k + 1][j];
                        })
                );
            }
        }

        return dp[1][a.size() - 2];

    }
};

