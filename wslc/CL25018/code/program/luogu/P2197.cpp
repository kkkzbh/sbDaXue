

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

fun solve()
{
    int n;
    std::cin >> n;
    std::vector<int> a;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,std::back_inserter(a));
    if(std::accumulate(range(a),int{},[](int x,int v){ return x ^ v; })) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while(t--) {
        std::invoke(solve);
    }
}