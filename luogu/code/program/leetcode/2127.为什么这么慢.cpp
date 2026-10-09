

#include<bits/stdc++.h>

#define fun auto
#define let auto
#define in :

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

using namespace std;
namespace sv = std::views;

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();

class Solution {
public:
    int maximumInvitations(vector<int>& data) {

        int n = int(data.size());

        let graph = std::vector(n,std::vector<int>{});
        let indeg = std::vector(n,0);

        for(let i in sv::iota(0,n)) {
            graph[i].push_back(data[i]);
            ++indeg[data[i]];
        }

        let tops = [&]() {

            let que = std::queue<int>{};
            for(let i in sv::iota(0,n) | sv::filter([&](int i){ return not indeg[i]; })) {
                que.push(i);
            }
            while(not que.empty()) {
                let it = que.front();
                que.pop();
                for(let i in graph[it]) {
                    if(not --indeg[i]) {
                        que.push(i);
                    }
                }
            }

        };

        tops();

        let vis = std::vector(n,false);
        let pairs = std::vector<std::pair<int,int>>{};
        let dfs = [&](int i) {
            let cnt = 1;
            let it = data[i];
            while(it != i) {
                vis[it] = true;
                it = data[it];
                ++cnt;
            }
            if(cnt == 2) {
                pairs.emplace_back(i,data[i]);
            }
            return cnt;
        };

        let res = std::ranges::max (
                sv::iota(0,n) | sv::filter([&](int i){ return indeg[i] and not vis[i]; }) | sv::transform([&](int i){ return dfs(i); })
        );

        let g = std::vector(n,std::vector<int>{});
        indeg.clear();

        for(let i in sv::iota(0,n)) {
            indeg[i] = int(graph[i].size());
            for(let v in graph[i]) {
                g[v].push_back(i);
            }
        }

        std::swap(graph,g);

        let bfs = [&,dfs = [&](auto& self,int x) {
            if(graph[x].empty()) {
                return 1;
            }
            return 1 + std::ranges::max (
                    graph[x] | sv::transform([&](int v){ return self(self,v); })
            );
        }](int x,int y) {
            return 2 +
                   (graph[x].size() == 1 ? 0 : std::ranges::max (
                           graph[x] | sv::filter([y](int i){ return i != y; }) | sv::transform([&](int i){ return dfs(dfs,i); })
                   ))
                   +
                   (graph[y].size() == 1 ? 0 : std::ranges::max (
                           graph[y] | sv::filter([x](int i){ return i != x; }) | sv::transform([&](int i){ return dfs(dfs,i); })
                   ));
        };


        let r =  pairs | sv::transform([&](auto pair){ return bfs(pair.first,pair.second); });

        return std::max (
                res,
                pairs.empty() ? 0 : std::reduce (r.begin(),r.end())
        );

    }
};




