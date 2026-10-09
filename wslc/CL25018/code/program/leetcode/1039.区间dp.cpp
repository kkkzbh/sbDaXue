

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

        return [&,f = [&,cache = std::vector(a.size(),std::vector(a.size(),0))](auto& self,int l,int r) mutable {
            if(r - l + 1 < 3) {
                return 0;
            }

            if(cache[l][r]) {
                return cache[l][r];
            }

            return cache[l][r] = std::ranges::min (
                    std::views::iota(l + 1,r) | std::views::transform([&,l,r](int i) {
                        return a[l] * a[r] * a[i] + self(self,l,i) + self(self,i,r);
                    })
            );

        }]() mutable {
            return f(f,0,int(a.size()) - 1);
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