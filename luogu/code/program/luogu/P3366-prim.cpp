

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
    int v,weight;
};

fun prim(std::vector<std::vector<node>>& graph,int start) -> std::optional<int>
{
    let vis = std::vector(graph.size(),false);
    let que = std::priority_queue<node,std::vector<node>,decltype([](node x,node y){ return x.weight > y.weight; })>{};
    vis[start] = true;
    for(let [v,weight] in graph[start]) {
        que.emplace(v,weight);
    }
    let cnt = 1;
    let ans = 0;
    while(not que.empty()) {
        let [v,weight] = que.top();
        que.pop();
        if(vis[v]) {
            continue;
        }
        vis[v] = true;
        ++cnt;
        ans += weight;
        for(let [vv,w] in graph[v]) {
            if(vis[vv]) {
                continue;
            }
            que.emplace(vv,w);
        }
    }
    if(cnt == graph.size()) {
        return ans;
    }
    return {};
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);

    int n,m;
    std::cin >> n >> m;
    let graph = std::vector(n,std::vector<node>{});
    for(let i in iota(0,m)) {
        int x,y,z;
        std::cin >> x >> y >> z;
        --x,--y;
        graph[x].emplace_back(y,z);
        graph[y].emplace_back(x,z);
    }
    let ans = prim(graph,0);
    if(ans) {
        std::cout << *ans;
    } else {
        std::cout << "orz";
    }

    return 0;
}


