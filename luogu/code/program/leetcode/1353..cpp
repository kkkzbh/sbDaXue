

#include<iostream>
#include<vector>
#include<ext/pb_ds/priority_queue.hpp>
#include<algorithm>
#include<ranges>

#define fun auto
#define let auto
#define in :

using namespace std;
using node = std::pair<int,int>;

class Solution {
public:
    fun static maxEvents(vector<vector<int>>& a)
    {
        let constexpr debug = false;
        std::ranges::sort(a,{},[](auto& vec){ return vec[0]; });
        let que = __gnu_pbds::priority_queue<node,decltype([](auto p1,auto p2) { return p1.second > p2.second; })>{};
        let bound = std::ranges::max(a | views::transform([](auto& vec){ return vec[1]; })) + 1;
        if constexpr(debug) {
            std::cout << std::format("bound = {}\n",bound);
        }
        let ans = 0;
        for(let it = a.cbegin(); let day in views::iota(1,bound)) {
            #define v (*it)
            while(it != a.cend() and v[0] == day) {
                que.push(node{ v[0],v[1] });
                ++it;
            }
            while(not que.empty() and que.top().second < day) {
                que.pop();
            }
            ans += que.empty() ? 0 : (que.pop(),1);
            if constexpr(debug) {
                std::cout << std::format("size of que is {}\n",que.size());
            }
        }
        return ans;
    }
};