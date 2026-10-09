

#include<bits/stdc++.h>

#define fun auto
#define let auto
#define in :

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

using namespace std::ranges::views;

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();


fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);

    let a = std::string{},b = a;
    std::getline(std::cin,a);
    std::getline(std::cin,b);
    int k;
    std::cin >> k;


    if(a.size() > b.size()) {
        std::swap(a,b);
    }

    let dfs = [&,k,n = int(a.size()),m = int(b.size()),vis = std::vector(a.size(),std::vector(b.size(),-1))](this auto& self,int l,int r) { // NOLINT
        if(l == n) {
            return k * (m - r);
        }
        if(r == m) {
            return k * (n - l);
        }
        if(vis[l][r] != -1) {
            return vis[l][r];
        }
        let v = std::abs(a[l] - b[r]);
//        if(v <= k) {
//            return vis[l][r] = v + self(l + 1,r + 1);
//        } else {
        return vis[l][r] = std::min ({
                                             k + self(l, r + 1),
                                             k + self(l + 1, r),
                                             v + self(l + 1, r + 1),
                                     });
//        }

    };

    std::cout << dfs(0,0);


    return 0;
}


