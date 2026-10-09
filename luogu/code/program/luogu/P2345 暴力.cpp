

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
    int v,x;
};

fun solve()
{
    int n;
    std::cin >> n;
    let a = std::vector(n,node{});
    for(auto& [v,x] : a) {
        std::cin >> v >> x;
    }
    int64 ans{};
    for(int i : iota(0,n - 1)) {
        for(int j : iota(i + 1,n)) {
            auto [vi,xi] = a[i];
            auto [vj,xj] = a[j];
            ans += std::max(vi,vj) * std::abs(xi - xj);
        }
    }
    std::cout << ans;
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}