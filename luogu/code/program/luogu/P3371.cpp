

#include<bits/extc++.h>

#define fun auto
#define let auto

namespace gnu
{
    using namespace __gnu_pbds;
    using namespace __gnu_cxx;
}

fun main() -> int
{

#define int long long

    int n,m,s;
    std::cin >> n >> m >> s;
    --s;
    using int64 = long long;
    using node = std::pair<int,int64>;  // v,w

    let graph = std::vector(n,std::vector<node>{});

    for(let i = 0; i != m; ++i) {
        int u,v,w;
        std::cin >> u >> v >> w;
        --u,--v;
        graph[u].emplace_back(v,w);
    }

    let constexpr INF64 = std::numeric_limits<int64>::max();

    let dijkstra = [INF64](auto& graph,int start){

        let n = signed(graph.size());
        let dis = std::vector(n,INF64);
        dis[start] = 0LL;

        let que_cmp = [](node p1,node p2) {
            return p1.second > p2.second;
        };
        using que_t = gnu::priority_queue<node,decltype(que_cmp)>;
        using que_it_t = typename que_t::point_iterator;

        let que = que_t{ que_cmp };
        let que_it = std::vector(n,que_it_t{});

        for(let i = 0; i != n; ++i) {
            que_it[i] = que.push({ i,dis[i] });
        }

        let vis = std::vector(n,false);

        while(not que.empty()) {
            let [it,_] = que.top();
            if(_ == INF64) {
                break;
            }
            que.pop();
            vis[it] = true;

            for(let [i,w] : graph[it]) {
                if(!vis[i] and dis[it] + w < dis[i]) {
                    dis[i] = dis[it] + w;
                    que.modify(que_it[i],{ i,dis[i] });
                }
            }
        }

        std::replace(dis.begin(),dis.end(),INF64,(1LL << 31) - 1LL);

        return dis;

    };


    let ans = dijkstra(graph,s);

    for(let v : ans) {
        std::cout << v << ' ';
    }

    return 0;
}