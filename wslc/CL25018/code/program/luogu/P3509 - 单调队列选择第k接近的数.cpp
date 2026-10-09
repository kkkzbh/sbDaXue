

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

constexpr int INF = std::numeric_limits<int>::max();
constexpr int64 INF64 = std::numeric_limits<int64>::max();

fun solve()
{
    int n,k;
    int64 m;
    std::cin >> n >> k >> m;
    let a = std::vector(n,int64{});
    for(int i : iota(0,n)) {
        std::cin >> a[i];
    }
    let to = std::vector(n,0);
    for(int it{},l{},r{ k }; it != n; ++it) {
        to[it] = std::ranges::max(l,r,{},[&,it](int i){ return std::abs(a[it] - a[i]); });
        while(it + 1 != n and r + 1 != n and a[r + 1] - a[it + 1] < a[it + 1] - a[l]) {
            ++l,++r;
        }
    }
    constexpr int step = 59 + 1;
    let st = std::vector(step,std::vector(n,0));
    for(int i : iota(0,n)) {
        st[0][i] = to[i];
    }
    for(int p : iota(1,step)) {
        for(int i : iota(0,n)) {
            st[p][i] = st[p - 1][st[p - 1][i]];
        }
    }
    for(int i : iota(0,n)) {
        int64 val = m;
        int it = i;
        for(int p : iota(0,step) | reverse) {
            if(int64 cnt = 1LL << p; val >= cnt) {
                val -= cnt;
                it = st[p][it];
            }
        }
        std::cout << it + 1 << ' ';
    }

}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}