

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

#if __cplusplus >= 202002L
#include<format>
#include<ranges>
#include<bit>
#include<span>
#endif

#define fun auto
#define let auto

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

#if __cplusplus >= 202002L
using namespace std::ranges::views;
#endif

constexpr int INF = std::numeric_limits<int>::max();
constexpr int64 INF64 = std::numeric_limits<int64>::max();

class Solution {
public:
    int nthMagicalNumber(int n, int a, int b)
    {
        int64 l{ std::min(a,b) },r{ n * l + 1 };
        let ok = [n,a,b,v = std::lcm(a,b)](int64 val) {
            return (val / a + val / b - val / v) >= n;
        };
        while(l != r) {
            int64 mid = (l + r) / 2;
            if(ok(mid)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return l % 1000000007;
    }
};