

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
    string largestNumber(vector<int>& a)
    {
        std::vector<std::string> sa;
        std::ranges::transform(a,std::back_inserter(sa),[](int v){ return std::to_string(v); });
        std::ranges::sort(sa,[](const std::string& s1,const std::string& s2){ return s1 + s2 > s2 + s1; });
        return sa[0] == "0" ? "0" : std::accumulate(range(sa),std::string{});
    }
};