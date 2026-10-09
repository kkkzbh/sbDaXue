

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

constexpr static int lgn = 100000 + 1;
constexpr static std::array<int,lgn> lg2 = []() consteval{
    std::array<int,lgn> a{};
    for(int i{ 2 }; i != lgn; ++i) {
        a[i] = a[i / 2] + 1;
    }
    return a;
}();

fun solve()
{
    int m,n;
    std::cin >> m >> n;
    let a = std::vector(m,0);
    for(auto& v : a) {
        std::cin >> v;
    }
    constexpr int step = 17;
    let st = std::vector(step,std::vector(m,0));
    for(int i : iota(0,m)) {
        st[0][i] = a[i];
    }
    for(int p : iota(1,step)) {
        for(int i : iota(0,m)) {
            st[p][i] = st[p - 1][i];
            int next = i + (1 << (p - 1));
            if(next < m) {
                st[p][i] = std::min(st[p][i],st[p - 1][next]);
            }
        }
    }
    let query = [&](int l,int r) {
        int cut = lg2[r - l + 1];
        return std::min(st[cut][l],st[cut][r - (1 << cut) + 1]);
    };
    while(n--) {
        int x,y;
        std::cin >> x >> y;
        std::cout << query(--x,--y) << ' ';
    }
    std::cout << '\n';
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}