

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
    bool predictTheWinner(vector<int>& a) {

        let p1 = [&,f = [&,cache = std::vector(a.size(),std::vector(a.size(),0))](auto& self,int l,int r) mutable{
            if(l == r) {
                return a[l];
            }
            if(l + 1 == r) {
                return std::ranges::max(a[l],a[r]);
            }
            if(cache[l][r]) {
                return cache[l][r];
            }

            return cache[l][r] = std::ranges::max(
                    a[l] + std::ranges::min(self(self,l + 2,r),self(self,l + 1,r - 1)),
                    a[r] + std::ranges::min(self(self,l + 1,r - 1),self(self,l,r - 2))
            );


        }]() mutable {
            return f(f,0,int(a.size() - 1));
        }();
        return p1 >= std::reduce(a.begin(),a.end()) - p1;
    }
};

#if check_ != leetcode
fun solve()
{

}

fun main() -> signed
{
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