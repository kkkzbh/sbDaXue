

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

    int n,m;
    std::cin >> n >> m;
    let a = std::vector(n,0);
    for(let &v in a) {
        std::cin >> v;
    }
    let l = 0,r = INF;

    let ok = [&,m](int mid) {
        let cut = 0;
        let v = 0;
        for(let i in iota(0,n)) {
            let res = v + a[i];
            if(res > mid) {
                v = a[i];
                ++cut;
            } else {
                v = res;
            }
        }

        return cut < m;
    };

    while(l != r) {
        //let mid = l + (r - l) / 2;
        let mid = (l + r) / 2;
        if(ok(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    std::cout << l;

    return 0;
}


