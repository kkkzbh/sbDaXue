

#include<iostream>
#include<format>
#include<vector>
#include<ext/pb_ds/priority_queue.hpp>
#include<ranges>
#include<algorithm>

#define fun auto
#define let auto
#define in :
#define print(...) std::cout << std::format(__VA_ARGS__)

using namespace std;
using node = std::pair<int,int>;

class Solution {
public:
    fun static findMaximizedCapital(int k, int w, vector<int>& p, vector<int>& c)
    {

        let n = int(p.size());
        let a = std::vector(n,node{});
        for(let i in views::iota(0,n)) {
            a[i] = node{ c[i],p[i] };
        }
        std::ranges::sort(a,{},[](auto p){ return p.first; });

        let que_cmp = [](node p1,node p2) {
            let const& [c1,w1] = p1;
            let const& [c2,w2] = p2;
            if(w1 == w2) {
                return c1 > c2;
            }
            return w1 < w2;
        };
        let que = __gnu_pbds::priority_queue<node,decltype(que_cmp)>{ que_cmp };

        for(let it = a.cbegin(); k; --k) { // NOLINT
            #define p (*it)
            #define cost p.first
            #define profit p.second
            for(; it != a.cend() and cost <= w; ++it) {
                que.push(node{ cost,profit });
            }
            if(que.empty()) {
                break;
            }
            let [mc,mp] = que.top();
            que.pop();
            w += mp;
        }

        return w;
    }
};