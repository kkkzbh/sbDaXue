

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
    int minScoreTriangulation(vector<int>& a) {

        return [&,f = [cache = map<std::vector<int>,int>{}](auto& self,const auto& r) mutable {
            if(r.size() == 3) {
                return std::reduce(r.begin(),r.end(),1,std::multiplies{});
            }
            if(let it = cache.find(r); it != cache.end()) {
                return it->second;
            }
            let a = std::vector(r.size() - 1,0);
            std::ranges::copy(r | std::views::take(r.size() - 1),a.begin());
            let ans = self(self,a) + r.front() * r.back() * r[r.size() - 2];
            for(let i in std::views::iota(0,int(r.size()) - 1) | std::views::reverse) {
                a[i] = r[i + 1];
                ans = std::min(ans,
                               self(self,a) + r[i] * r[i + 1] * (i ? r[i - 1] : r.back())
                );
            }

            return ans;
        }]() mutable {
            return f(f,a);
        }();

    }
};

#if check_ != leetcode
fun solve() {

}

fun main() -> signed {
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
#endif