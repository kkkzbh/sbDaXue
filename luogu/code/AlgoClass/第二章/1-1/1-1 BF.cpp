

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

fun solve(auto& is,auto& os)
{
    int n;
    is >> n;
    std::vector a(10,int64{});
    for(int i{ 1 }; i <= n; ++i) {
        int val{ i };
        for(; val; val /= 10) {
            ++a[val % 10];
        }
    }
    std::ranges::copy(a,std::ostream_iterator<int64>{ os,"\n" });
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    for(int i{}; i <= 0; ++i) {
        std::ifstream is{ std::format("../AlgoClass/1-1/test/count{}.in",i) };
        std::ofstream os{ std::format("../AlgoClass/1-1/out/ans{}.out",i) };
        solve(std::cin,std::cout);
    }
}