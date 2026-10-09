

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>
#include<cmath>
#include<numeric>
#include<cstring>
#include<functional>
#include<string>
#include<bitset>
#include<unordered_map>
#include<deque>
#include<queue>
#include<optional>
#include<unordered_set>
#include<cassert>
#include<stack>

#define fun auto
#define var auto
#define cast static_cast
#define range(A) A.begin(),A.end()

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;
using namespace std::views;

constexpr int INF{ 1000000000 + 520 };
constexpr int64 LNF { 66666666666666666 };
constexpr int N{ 1000 };

consteval fun presum()
{
    std::array<int,N> a;
    a[0] = 1;
    for(int i : iota(1,N)) {
        a[i] = a[i - 1] + (i + 1);
    }
    return a;
}

constexpr var sum{ presum() };

fun solve()
{
    int n,m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> a(n,std::vector<int>(m));
    for(int i : iota(0,n)) {
        for(int j : iota(0,m)) {
            char c;
            std::cin >> c;
            a[i][j] = c == '.' ? 1 : 0;
        }
    }
    int64 ans{};
    for(int i : iota(0,n)) {
        if(i) {
            for(int j: iota(0, m)) {
                a[i][j] = a[i][j] ? a[i - 1][j] + 1 : 0;
            }
        }
        std::stack<int,std::vector<int>> stk;
        auto& v{ a[i] };
        v.push_back(-INF);
        for(int j : iota(0,m + 1)) {
            while(!stk.empty() and v[j] < v[stk.top()]) {
                int it{ stk.top() };
                stk.pop();
                int l{ stk.empty() ? -1 : stk.top() };
                ans += (it - l) * (j - it) * v[it];
            }
            stk.push(j);
        }
    }
    std::cout << ans << '\n';

}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}