

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
    let ldmap = std::map<char,int>{};
    let lemap = std::map<char,int>{};
    let rdmap = std::map<char,int>{};
    let remap = std::map<char,int>{};

    let insert = [](char c,auto& map) {
        ++map[c];
    };

    let pop = [](char c,auto& map) {
        --map[c];
    };

    for(let [i,c] in enumerate(s)) {
        if(i & 1) {
            insert(c,rdmap);
        } else {
            insert(c,remap);
        }
    }

    if(n & 1) {
        let ans = INF;
        --n;
        n /= 2;
        for(let [cut,c] in enumerate(s)) {
            if(cut & 1) {
                pop(c,rdmap);
            } else {
                pop(c,remap);
            }

            let map1 = std::map<char,int>{};
            map1['$'] = 0;
            for(let [ch,cnt] in ldmap) {
                map1[ch] += cnt;
            }
            for(let [ch,cnt] in remap) {
                map1[ch] += cnt;
            }
            let map2 = std::map<char,int>{};
            map2['$'] = 0;
            for(let [ch,cnt] in lemap) {
                map2[ch] += cnt;
            }
            for(let [ch,cnt] in rdmap) {
                map2[ch] += cnt;
            }

            ans = std::ranges::min(ans,
                                   (n - std::ranges::max(map1 | values)) + (n - std::ranges::max(map2 | values)));
            if(cut & 1) {
                insert(c,ldmap);
            } else {
                insert(c,lemap);
            }
        }
        std::cout << ans + 1 << ' ';
    } else {
        n /= 2;
        std::cout << (n - std::ranges::max(rdmap | values)) + (n - std::ranges::max(remap | values));
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