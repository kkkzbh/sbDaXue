

#include<bits/stdc++.h>

#define fun auto
#define let auto
#define in :

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

using namespace std;
namespace stv = std::ranges::views;

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();


struct Solution {

    vector<int> loudAndRich(vector<vector<int>>& side, vector<int>& a) {

        let ideg = std::vector(a.size(),0);
        let graph = std::vector(a.size(),std::vector<int>{});

        for(let vec in side) {
            let [x,y] = std::make_pair(vec[0],vec[1]);
            graph[x].push_back(y);
            ++ideg[y];
        }

        let ans = std::vector(a.size(),0);
        std::iota(ans.begin(),ans.end(),0);
        let que = std::queue<int>{};
        for(let v in stv::iota(0,int(a.size())) | stv::filter([&](int i){ return not ideg[i]; })) {
            que.push(v);
            std::cout << v << ' ';
        }

        while(not que.empty()) {
            let it = que.front();
            que.pop();

            for(let i in graph[it]) {
                if(a[ans[it]] < a[i]) {
                    a[i] = a[ans[it]];
                    ans[i] = ans[it];
                }
                if(not --ideg[i]) {
                    que.push(i);
                }
            }
        }

        return ans;

    }

};

