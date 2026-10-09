

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

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

#if __cplusplus >= 202002L
using namespace std::ranges::views;
#endif

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();

fun solve()
{
    int n,k,q;
    std::cin >> n >> k >> q;
    let a = std::vector(n,0);
    for(auto& v : a) {
        std::cin >> v;
    }

    let set = std::multiset<int>{};
    let map = std::map<int,int>{};

    for(int i : iota(0,n)) {
        set.insert(0);
    }
    for(int i : iota(0,k - 1)) {
        set.erase(set.find(map[a[i]]));
        ++map[a[i]];
        set.insert(map[a[i]]);
    }

    let ans = std::vector(n - k + 1,0);

    for(int i : iota(k - 1,n)) {
        set.erase(set.find(map[a[i]]));
        ++map[a[i]];
        set.insert(map[a[i]]);

        int it = i - k + 1;
        ans[it] = k - *set.rbegin();

        set.erase(set.find(map[a[it]]));
        ++map[a[it]];
        set.insert(map[a[it]]);

    }



}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while(t--) {
        std::invoke(solve);
    }
}