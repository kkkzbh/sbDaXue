

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

enum { luogu,codeforces };
let constexpr check_ = codeforces;

class Solution {
public:
    int minInsertions(string& s) {

        // dp[l][r] = dp[l + 1][r - 1] or min -> dp[l + 1][r] | dp[l][r - 1]

        let dp = std::vector(s.size(),std::vector(s.size(),0));
        struct array {
            using T = decltype(dp);
            T& e;
            explicit array(T& e) : e{ e }{}
            fun operator[](int l,int r){
                if(l > r) {
                    return 0;
                }
                return e[l][r];
            }
        }a{ dp };

        for(let l = int(s.size() - 1); l >= 0; --l) {
            for(let r = l + 1; r <= int(s.size()); ++r) {
                if(s[l] == s[r - 1]) {
                    dp[l][r - 1] = a[l + 1,r - 2];
                } else {
                    dp[l][r - 1] = 1 + std::ranges::min(a[l + 1,r - 1],a[l,r - 2]);
                }
            }
        }

        return dp[0][int(s.size()) - 1];
    }
};

#if check_ != leetcode
fun main() -> signed {
    std::string s{ "mbadm" };
    std::cout << Solution{}.minInsertions(s);
    return char{};
};
#endif