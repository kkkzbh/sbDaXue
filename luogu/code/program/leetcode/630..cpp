

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>
#include<cmath>
#include<numeric>
#include<cstring>
#include<functional>
#include<string>
#include<bitset>
#include<unordered_map>
#include<deque>
#include<queue>
#include<optional>
#include<unordered_set>
#include<cassert>

#define fun auto
#define var auto
#define cast static_cast
#define range(A) A.begin(),A.end()

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;
using namespace std;

constexpr int INF{ 1000000000 + 520 };
constexpr int64 LNF { 66666666666666666 };

class Solution {
public:
    int scheduleCourse(vector<vector<int>>& a)
    {
        std::ranges::sort(a,std::less<>{},[](const auto& v){ return v.back(); });
        int ans{};
        std::priority_queue<int> que;
        std::ranges::for_each(a,[&que,&ans,i = 0](const auto& v) mutable {
            var [duration,lastday]{ std::tie(v[0],v[1]) };
            if(i + duration <= lastday) {
                i += duration;
                ++ans;
                que.push(duration);
            } else if(!que.empty() and duration < que.top()) {
                i = i - que.top() + duration;
                que.pop();
                que.push(duration);
            }
        });
        return ans;
    }
};