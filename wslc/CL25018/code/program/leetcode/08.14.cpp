

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

using node = std::array<int,2>;

class Solution {
public:
    int static countEval(string& s, int result) {

        return [&,f = [&,dp = std::vector(s.size(),std::vector(s.size(),node{})),cache = [](node v) -> bool { return v[0] or v[1]; }](auto& self,int l,int r) mutable -> node {
            if(l == r) {
                let num = s[l] ^ 48;
                return { num ^ 1,num };
            }
            if(cache(dp[l][r])) {
                return dp[l][r];
            }
            let f = 0,t = 0;
            for(let i = l + 1; i < r; i += 2) {
                let [lf,lt] = self(self,l,i - 1);
                let [rf,rt] = self(self,i + 1,r);
                switch(s[i]) {
                    case '&': { f += lf * rf + lf * rt + lt * rf,t += lt * rt; } break;
                    case '|': { f += lf * rf,t += lf * rt + lt * rf + lt * rt; } break;
                    case '^': { f += lf * rf + lt * rt,t += lf * rt + lt * rf; } break;
                }
            }
            return dp[l][r] = { f,t };

        }]() mutable {
            return f(f,0,int(s.size()) - 1);
        }()[result];

    }
};