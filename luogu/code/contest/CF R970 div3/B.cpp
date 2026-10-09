

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

#if __cplusplus >= 202002L
using namespace std::ranges::views;
#endif

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();

enum { luogu,codeforces };
let constexpr check = codeforces;

fun solve()
{
    let n = 0;
    let s = std::string{};
    std::cin >> n >> s;
    if(s == "1" or s == "1111") {
        std::cout << "YES" << '\n';
        return;
    }
    let cnt = 0;
    while(s[cnt] == '1') {
        ++cnt;
    }
    --cnt;
    let end = n - 1;
    while(s[end] == '1') {
        --end;
    }
    ++end;
    if(cnt != n - 1 - end or n - (2LL * cnt) != (cnt - 2LL) * cnt) {
        std::cout << "NO" << '\n';
        return;
    }

    let dfs = [&,cnt,f = [&,depcei = cnt - 2,cut = "1" + std::string(cnt - 2,'0') + "1" ](auto& self,int i,int dep) {
        if(dep == depcei) {
            return true;
        }
        if(!s.compare(i,depcei + 2,cut)) {
            return self(self,i + depcei + 2,dep + 1);
        }
        return false;

    }]() {
        return f(f,cnt,0);
    };

    std::cout << std::array{ "NO","YES" }[dfs()] << '\n';

}

fun main() -> signed
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    if constexpr(check == codeforces) {
        let t = 0;
        std::cin >> t;
        while(t--) {
            std::invoke(solve);
        }
    } else {
        std::invoke(solve);
    }
}