

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
    std::vector big(n,n);
    for(int i : iota(0,n)) {
        while(!stk.empty() and d(i) > d(stk.top())) {
            int top = stk.top();
            stk.pop();
            big[top] = i;
        }
        stk.push(i);
    }
    constexpr int step = 16 + 1;
    let st = std::vector(step,std::vector(n + 1,node{}));
    for(int p : iota(0,step)) {
        st[p][n] = { n,INF / 2 };
    }
    for(int i : iota(0,n)) {
        st[0][i] = { big[i],c(i) };
    }
    for(int p : iota(1,step)) {
        for(int i : iota(0,n)) {
            st[p][i] = {
                    st[p - 1][st[p - 1][i].d].d,
                    std::min(st[p - 1][i].c + st[p - 1][st[p - 1][i].d].c,INF / 2)
            };
        }
    }
    let query = [&](int r,int v) {
        for(int i{ step }; i--;) {
            if(v > st[i][r].c) {
                v -= st[i][r].c;
                r = st[i][r].d;
            }
        }
        return r;
    };
    while(q--) {
        int r,v;
        std::cin >> r >> v;
        int pos = query(--r,v);
        std::cout << (pos == n ? 0 : pos + 1) << '\n';
    }
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}