

#include<bits/stdc++.h>

#define fun auto
#define let auto
#define in :

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

using namespace std;

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();

class Solution {
public:
    int static maximumInvitations(vector<int>& graph) {
        int n = int(graph.size());
        let indeg = std::vector(n,0);

        std::ranges::for_each(graph,[&](int v){ ++indeg[v]; });
        let dep = std::vector(n,1);
        let que = std::queue<int>{};
        for(let v in std::views::iota(0,n) | std::views::filter([&](int v){ return not indeg[v]; })) {
            que.push(v);
        }
        while(not que.empty()) {
            let it = que.front();
            que.pop();
            let v = graph[it];
            dep[v] = std::max(dep[v],dep[it] + 1);
            if(not --indeg[v]) {
                que.push(v);
            }
        }
        let sc = 0,bc = 0;
        for(let v in std::views::iota(0,n) | std::views::filter([&](int v){ return indeg[v]; })) {
            indeg[v] = 0;
            let it = graph[v];
            let cnt = 1;
            while(indeg[it]) {
                indeg[it] = 0;
                it = graph[it];
                ++cnt;
            }
            if(cnt == 2) {
                sc += dep[v] + dep[graph[v]];
            } else {
                bc = std::max(bc,cnt);
            }
        }
        return std::max(sc,bc);

    }
};





