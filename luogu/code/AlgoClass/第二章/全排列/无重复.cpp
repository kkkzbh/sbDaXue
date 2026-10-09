

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

    let ans = std::vector<std::vector<int>>{};

    let fp = [&,f = [&,n](auto& self,int i) mutable -> void {
        if(i > n) {
            ans.push_back(a);
            return;
        }
        for(int k : iota(i,n + 1)) {
            std::swap(a[i - 1],a[k - 1]);
            self(self,i + 1);
            std::swap(a[i - 1],a[k - 1]);
        }
    }] mutable{
        f(f,1);
    };

    fp();

    std::ranges::sort(ans);

    for(auto& vec : ans) {
        for(auto val : vec) {
            std::cout << std::format("{:5d}",val);
        }
        std::cout << '\n';
    }

}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}