

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
    std::string s;
    std::cin >> s;
    std::ranges::sort(s);
    let vis = std::vector(n,false);

    int cnt{};
    let fp = [&,f = [&,n,str = std::string{}](auto& self,int i) mutable -> void {
        if(i == n) {
            std::cout << str << '\n';
            ++cnt;
            return;
        }
        std::set<int> set;
        for(int k : iota(0,n) | filter([&](int k){ return !vis[k] and !set.contains(s[k]); })) {
            set.insert(s[k]);
            vis[k] = true;
            str.push_back(s[k]);
            self(self,i + 1);
            str.pop_back();
            vis[k] = false;
        }
    }]() mutable {
        f(f,0);
    };

    fp();
    std::cout << cnt;

}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}