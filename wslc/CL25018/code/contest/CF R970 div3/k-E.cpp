

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
let constexpr check_ = codeforces;

fun solve()
{
    int n;
    std::cin >> n;
    let s = std::string{};
    std::cin >> s;
    let ldset = std::multiset<int>{};
    let ldmap = std::map<char,int>{};
    let leset = std::multiset<int>{};
    let lemap = std::map<char,int>{};
    let rdset = std::multiset<int>{};
    let rdmap = std::map<char,int>{};
    let reset = std::multiset<int>{};
    let remap = std::map<char,int>{};

    let insert = [](char c,auto& set,auto& map) {
        let &v = map[c];
        let it = set.find(v);
        if(it != set.end()) {
            set.erase(it);
        }
        set.insert(++v);
    };

    let pop = [](char c,auto& set,auto& map) {
        let &v = map[c];
        set.erase(set.find(v));
        set.insert(--v);
    };

    for(let [i,c] in enumerate(s)) {
        if(i & 1) {
            insert(c,rdset,rdmap);
        } else {
            insert(c,reset,remap);
        }
    }

    if(n & 1) {
        let ans = INF;
        for(let [cut,c] in enumerate(s)) {
            if(cut & 1) {
                pop(c,rdset,rdmap);
            } else {
                pop(c,reset,remap);
            }
            let ldcnt = cut / 2;
            let lecnt = cut - cut / 2;
            let rdcnt = (n - cut) / 2 - (cut & 1);
            let recnt = (n + 1 + cut) / 2 - cut - (cut & 1 ^ 1);
            ans = std::min<int>(ans,
                                (ldcnt - (ldset.empty() ? 0 : *ldset.rbegin())) + (recnt - (reset.empty() ? 0 : *reset.rbegin()))
                                + (lecnt - (leset.empty() ? 0 : *leset.rbegin())) + (rdcnt - (rdset.empty() ? 0 : *rdset.rbegin()))
            );
            if(cut & 1) {
                insert(c,ldset,ldmap);
            } else {
                insert(c,leset,lemap);
            }
            std::cout << ans + 1 << ' ';
        }
    } else {
        n /= 2;
        std::cout << (n - *rdset.rbegin()) + (n - *reset.rbegin());
    }

    std::cout << '\n';

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