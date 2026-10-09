

#include<bits/extc++.h>

#define fun auto
#define let auto
#define in :

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

using namespace std::ranges::views;

namespace gnu
{
    using namespace __gnu_pbds;
    using namespace __gnu_cxx;
}

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();


fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);

    int n,m,s,t;
    std::cin >> n >> m >> s >> t;
    --s,--t;
    using node = std::pair<int,int>;

    let a = std::vector(n,std::vector<node>{});

    for(let i in iota(0,m)) {
        int u,v,w;
        std::cin >> u >> v >> w;
        --u,--v;
        a[u].emplace_back(v,w);
        a[v].emplace_back(u,w);
    }

    let dijkstra = [n](int start,int go,const auto& graph) {

        let constexpr INF = std::numeric_limits<int>::max();
        let constexpr INF64 = std::numeric_limits<int64>::max();

        let dis = std::vector(n,INF64);
        dis[start] = 0;

        using que_node = std::pair<int,int64>;
        using que_t =  gnu::priority_queue<que_node,decltype([](que_node x,que_node y) {
            return x.second > y.second;
        })>;
        using que_it_t = que_t::point_iterator;

        let que_it = std::vector(n,que_it_t{});
        let que = que_t{};

        for(let i in iota(0,n)) {
            que_it[i] = que.push({ i,dis[i] });
        }

        let vis = std::vector(n,false);

        while(not que.empty()) {
            let [it,_] = que.top();
            que.pop();
            vis[it] = true;

            for(let [i,w] in graph[it] | filter([&](que_node i){ return not vis[i.first]; })) {
                if(let d = dis[it] + w; d < dis[i]) {
                    dis[i] = d;
                    que.modify(que_it[i],{ i,dis[i] });
                }
            }
        }

        return dis[go];

    };

    std::cout << dijkstra(s,t,a);


    return 0;
}


