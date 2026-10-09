

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
    int n;
    std::cin >> n;
    let a = std::vector(n,0);
    std::iota(a.begin(),a.end(),1);
    int cei{ 1 };
    for(int i : iota(2,n + 1)) {
        cei *= i;
    }
    for(auto v : a) {
        std::cout << std::format("{:5d}",v);
    }
    std::cout << '\n';
    for(int i : iota(1,cei)) {
        std::ranges::next_permutation(a);
        for(auto v : a) {
            std::cout << std::format("{:5d}",v);
        }
        std::cout << '\n';
    }

}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}