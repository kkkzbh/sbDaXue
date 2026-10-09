

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
#define in :

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

#if __cplusplus >= 202002L
using namespace std::ranges::views;
#endif

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();

enum { luogu,codeforces };
let constexpr check_ = luogu;

fun solve()
{
    int n;
    int64 m;
    std::cin >> n >> m;

    using vec = std::vector<int64>;
    using vec_t = vec::value_type;

    let a = vec(n,0LL);
    std::copy_n(std::istream_iterator<vec_t>{ std::cin },n,a.begin());

    let bfs = [&] {

        let lans = vec{};
        let rans = vec{};

        let dfs = [&,f = [&,m](auto& self,int i,int bound,int64 v,auto& ans) {
            if(i == bound) {
                ans.push_back(v);
                return;
            }
            self(self,i + 1,bound,v,ans);
            if(v + a[i] <= m) {
                self(self,i + 1,bound,v + a[i],ans);
            }

        }](int i,int bound,auto& ans) {
            f(f,i,bound,0,ans);
        };

        let mid = n / 2;

        dfs(0,mid,lans);
        dfs(mid,n,rans);

        std::ranges::sort(lans);
        std::ranges::sort(rans);

        let ans = 0LL;
        for(let l = 0,r = int(rans.size()) - 1; l != int(lans.size()); ++l) {
            while(lans[l] + rans[r] > m) {
                --r;
            }
            ans += r + 1;
        }

        return ans;

    };

    std::cout << bfs();

}

fun main() -> signed
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    if constexpr(check_ == codeforces) {
        let t = 0;
        std::cin >> t;
        while(t--) {
            std::invoke(solve);
        }
    } else {
        std::invoke(solve);
    }
    return 0;
}