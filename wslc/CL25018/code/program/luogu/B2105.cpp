

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

#if __cplusplus >= 202002L
#include<format>
#include<ranges>
#include<bit>
#include<span>
#endif

#define fun auto
#define main fun main
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
    int n,m,k;
    std::cin >> n >> m >> k;
    std::vector<std::vector<int>> a(n,std::vector<int>(m)),b(m,std::vector<int>(k)),c(n,std::vector<int>(k));
    for(auto& v : a) {
        std::copy_n(std::istream_iterator<int>{ std::cin },m,v.begin());
    }
    for(auto& v : b) {
        std::copy_n(std::istream_iterator<int>{ std::cin },k,v.begin());
    }
    for(int i : iota(0,n)) {
        for(int v : iota(0,m)) {
            for(int j : iota(0,k)) {
                c[i][j] += a[i][v] * b[v][j];
            }
        }
    }
    for(auto& v : c) {
        std::ranges::copy(v,std::ostream_iterator<int>{ std::cout," " });
        std::cout << '\n';
    }

}

main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}