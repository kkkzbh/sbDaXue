

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
    int i{};
    let ok = [&]{
        int cnt{};
        for(char c : std::format("{:010b}",i)) {
            if(c == '1') {
                if(++cnt >= 3) {
                    return true;
                }
            } else {
                cnt = 0;
            }
        }
        return false;
    };
    constexpr int ceil = 1 << 10;
    int cnt{};
    for(; i <= ceil; ++i) {
        if(ok()) {
            ++cnt;
        }
    }
    std::cout << std::format("{}/{}",cnt,ceil);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}