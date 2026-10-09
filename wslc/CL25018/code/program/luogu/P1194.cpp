

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

struct node
{

    fun friend operator<=>(node x,node y)
    {
        return x.w <=> y.w;
    }

    int v;
    int w;
};

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int k,n;
    std::cin >> k >> n;
    let a = std::vector(n,std::vector(n,0));
    for(let &vec in a) {
        for(let &v in vec) {
            std::cin >> v;
            if(not v) {
                v = k;
            }
        }
    }

    let ans = std::ranges::min(iota(0,1) | transform([&,k,n](int start) {

        let que = std::priority_queue<node,std::vector<node>,std::greater<>>{};
        let vis = std::vector(n,false);
        vis[start] = true;
        let cnt = 1;
        for(let i in iota(0,start)) {
            que.emplace(i,a[start][i]);
        }
        for(let i in iota(start + 1,n)) {
            que.emplace(i,a[start][i]);
        }
        let ans = k;
        while(not que.empty()) {
            let [v,w] = que.top();
            que.pop();
            if(vis[v]) {
                continue;
            }
            vis[v] = true;
            ++cnt;
            ans += std::min(w,k);
            for(let i in iota(0,v) | filter([&](int i){ return not vis[i]; })) {
                que.emplace(i,a[v][i]);
            }
            for(let i in iota(v + 1,n) | filter([&](int i){ return not vis[i]; })) {
                que.emplace(i,a[v][i]);
            }
        }
        return ans;

    }));

    std::cout << ans << '\n';

    return 0;
}


