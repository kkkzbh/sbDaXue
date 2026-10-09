


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

#define fun auto constexpr
#define var auto
#define cast static_cast
#define range(A) A.begin(),A.end()


using int64 = long long;
using uint64 = unsigned long long;
using namespace std;

constexpr int INF{ 1000000000 + 520 };
constexpr int64 LNF { 66666666666666666 };

class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs)
    {
        std::vector<int> a;
        std::ranges::transform(costs,std::back_inserter(a),[](auto& v){ return v[1] - v[0]; });
        std::ranges::partial_sort(a,a.begin() + (costs.size() >> 1));
        int sum{ std::accumulate(costs.begin(),costs.end(),int{},[](int x,auto& v){ return x + v[0]; }) };
        return std::accumulate(a.begin(),a.begin() + (costs.size() >> 1),sum);
    }
};