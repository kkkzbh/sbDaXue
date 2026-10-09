

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

struct node
{
    int d,c;
};

fun solve()
{
    int n,q;
    std::cin >> n >> q;
    std::vector a(n,node{});
    for(auto& [d,c] : a) {
        std::cin >> d >> c;
    }
    std::stack<int> stk;
    let d = [&](int i){ return a[i].d; };
    let c = [&](int i){ return a[i].c; };
    std::vector big(n,-1);
    for(int i : iota(0,n)) {
        while(!stk.empty() and d(i) > d(stk.top())) {
            int top = stk.top();
            stk.pop();
            big[top] = i;
        }
        stk.push(i);
    }
    while(q--) {
        int r,v;
        std::cin >> r >> v;
        --r;
        while(v - c(r) > 0 and r != -1) {
            v -= c(r);
            r = big[r];
        }
        std::cout << (r == -1 ? 0 : r + 1) << '\n';
    }
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}