

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
    int minInsertions(string& s)
    {

        return [&,f = [&,dp = std::vector(s.size(),std::vector(s.size(),-1))](auto& self,int l,int r) mutable {
            if(l >= r) {
                return 0;
            }

            if(dp[l][r - 1] != -1) {
                return dp[l][r - 1];
            }

            if(s[l] == s[r - 1]) {
                return dp[l][r - 1] = self(self,l + 1,r - 1);
            }
            return dp[l][r - 1] = 1 + std::ranges::min(self(self,l + 1,r),self(self,l,r - 1));

        }]() mutable {
            return f(f,0,int(s.size()));
        }();

    }
};