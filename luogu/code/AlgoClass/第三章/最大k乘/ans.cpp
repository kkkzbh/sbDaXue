

#include<bits/stdc++.h>
#include<print>

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

    int n,k;
    std::cin >> n >> k;
    let s = std::string{};
    std::cin >> s;
    let a = std::vector(n,0);
    for(let i in iota(0,n)) {
        a[i] = s[i] - '0';
    }

    let dfs = [&,r = n - 1](this auto& self,int l,int cnt) -> int64 {    // NOLINT
        if(not cnt) {
            let v = 0;
            for(let i in iota(l,r + 1)) {
                v *= 10;
                v += a[i];
            }
            return v;
        }

        let v = a[l];
        let ans = 0LL;
        for(let i in iota(l + 1,r - cnt + 2)) {
            ans = std::max(ans,v * self(i,cnt - 1));
            v *= 10;
            v += a[i];
        }

        return ans;

    };
    let ans = dfs(0,k - 1);
    std::println("{}",ans);

    return 0;
}


