

#include<bits/extc++.h>

#define let auto
#define fun auto
#define in :

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m,k,s,t;
    std::cin >> n >> m >> k >> s >> t;
    using node = std::pair<int,int>;
    let g = std::vector(n,std::vector<node>{});
    using namespace std::views;
    for(int a,b,c; let _ in iota(0,m)) {
        std::cin >> a >> b >> c;
        g[a].emplace_back(b,c);
        g[b].emplace_back(a,c);
    }
    std::cout << [&] {
        let constexpr INF = std::numeric_limits<int>::max();
        let dis = std::vector(n,std::vector(k + 1,INF));
        dis[s][k] = 0;
        let que_cmp = [&,compare = std::greater{}](node x,node y) {
            let const& [v1,w1] = x;
            let const& [v2,w2] = y;
            return compare(dis[v1][w1],dis[v2][w2]);
        };
        let que = __gnu_pbds::priority_queue<node,decltype(que_cmp)>{ que_cmp };
        let q = std::vector(n,std::vector(k + 1,decltype(que)::point_iterator{}));
        for(let i in iota(0,n)) {
            for(let j in iota(0,k + 1)) {
                q[i][j] = que.push({ i,j });
            }
        }

        while(not que.empty()) {
            let [it,cnt] = que.top();
            if(it == t) {
                return dis[it][cnt];
            }
            que.pop();
            for(let [i,c] in g[it]) {
                if(cnt and dis[it][cnt] < dis[i][cnt - 1]) {
                    dis[i][cnt - 1] = dis[it][cnt];
                    que.modify(q[i][cnt - 1],*q[i][cnt - 1]);
                }
                if(dis[it][cnt] + c < dis[i][cnt]) {
                    dis[i][cnt] = dis[it][cnt] + c;
                    que.modify(q[i][cnt],*q[i][cnt]);
                }
            }
        }

        return -1;

    }();

    return 0;
};