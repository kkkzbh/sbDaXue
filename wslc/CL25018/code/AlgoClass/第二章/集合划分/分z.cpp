

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
#include<format>
#include<ranges>
#include<bit>
#include<span>

#define fun auto
#define let auto
#define in :

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

using namespace std::ranges::views;

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();

enum { luogu,codeforces,leetcode };
let constexpr check_ = luogu;


fun solve() {
    int n,m;
    std::cin >> n >> m;

    let dfs = [c = std::vector(n + 1,std::vector(m + 1,-1))](this auto& self,int n,int m) { // NOLINT
        if(n == m or m == 1) {
            return 1;
        }
        if(n < m) {
            return 0;
        }
        if(c[n][m] != -1) {
            return c[n][m];
        }
        return c[n][m] = m * self(n - 1,m) + self(n - 1,m - 1);
    };

    std::cout << dfs(n,m);

}

fun main() -> signed {
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    if constexpr(check_ == codeforces) { // NOLINT
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
