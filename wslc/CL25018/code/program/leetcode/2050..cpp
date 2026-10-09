

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
    int minimumTime(int n, vector<vector<int>>& side, vector<int>& a) {

        let graph = std::vector(n,std::vector<int>{});
        let ideg = std::vector(n,0);
        let odeg = std::vector(n,0);

        for(let &v in side) {
            let [x,y] = std::make_pair(v[0],v[1]);
            --x,--y;
            graph[x].push_back(y);
            ++ideg[y];
            ++odeg[x];
        }

        namespace stv = std::views;

        let que = std::queue<int>{};
        let vec = std::vector(n,0);
        for(let i in stv::iota(0,n) | stv::filter([&](int i){ return not ideg[i]; })) {
            que.push(i);
        }
        while(not que.empty()) {
            let it = que.front();
            que.pop();

            for(let i in graph[it]) {
                vec[i] = std::max(vec[i],vec[it] + a[it]);
                if(not --ideg[i]) {
                    que.push(i);
                }
            }

        }

        let ans = std::ranges::max (
                stv::iota(0,n) | stv::filter([&](int i){ return not odeg[i]; }) | stv::transform([&](int i){ return vec[i] + a[i]; })
        );

        return ans;

    }
};




