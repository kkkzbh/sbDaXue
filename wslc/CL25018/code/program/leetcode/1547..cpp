

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
let constexpr check_ = leetcode;

class Solution {
public:
    int minCost(int n, vector<int>& a) {
        std::ranges::sort(a);
        return [&,f = [&,c = std::vector(a.size(),std::vector(a.size(),0))](auto& self,int l,int r,int cl,int cr) mutable {
            if(cl > cr) {
                return 0;
            }
            if(cl == cr) {
                return r - l;
            }
            if(c[cl][cr]) {
                return c[cl][cr];
            }
            return c[cl][cr] = std::ranges::min(
                    std::views::iota(cl,cr + 1) | std::views::transform([&,l,r](int i) {
                        return r - l + self(self,l,a[i],cl,i - 1) + self(self,a[i],r,i + 1,cr);
                    }));
        }]() mutable {
            return f(f,0,n,0,int(a.size()) - 1);
        }();
    }
};

