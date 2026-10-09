

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
    let a = std::vector(n,0);
    for(let &v in a) {
        std::cin >> v;
        --v;
    }
    let s = std::string{};
    std::cin >> s;
    let circle = std::vector<std::vector<int>>{};
    /*
     *  we may not need to use circle to record which i in where circle,
     *  because when we firstly traverse and collect i to circle where they should be
     *  and we let vis[i] = true bic[the circle] = cnt
     *  Through the firstly traverse,we get the cnt and make vis[i] equal true
     *  but why we not traverse again,and let answer of i which in the circle equal cnt ?
     */
    let bic = std::vector<int>{};
    let vis = std::vector(n,false);
    for(let i in iota(0,n) | filter([&](int i){ return !vis[i]; })) {
        circle.emplace_back();
        bic.emplace_back();
        let &vec = circle.back();
        let &cnt = bic.back();
        vis[i] = true;
        vec.push_back(i);
        if(s[i] == '0') {
            ++cnt;
        }
        let it = a[i];
        for(; it != i; it = a[it]) {
            vec.push_back(it);
            vis[it] = true;
            if(s[it] == '0') {
                ++cnt;
            }
        }
    }
    let ans = std::vector(n,0);
    for(let [i,v] in circle | enumerate) {
        for(let val in v) {
            ans[val] = bic[i];
        }
    }
    std::ranges::copy(ans,std::ostream_iterator<int>{ std::cout," " });
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