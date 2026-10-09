

#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<numeric>
#include<cstring>
#include<functional>
#include<string>
#include<bitset>
#include<deque>
#include<queue>
#include<cassert>
#include<stack>
#include<optional>
#include<array>
#include<unordered_set>
#include<unordered_map>
#include<map>
#include<set>
#include<fstream>

#if __cplusplus >= 202002L
#include<format>
#include<ranges>
#include<bit>
#include<span>
#endif

#define fun auto
#define let auto
#define in :

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

using namespace std;

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();

enum { luogu,codeforces,leetcode };
let constexpr check_ = codeforces;

class Solution {
public:
    int minCost(int n, vector<int>& a) {

        a.push_back(n);
        a.insert(a.begin(),0);
        std::ranges::sort(a);

        let d = std::vector(a.size(),std::vector(a.size(),0));

        // [1 - size() - 2]

        for(let i in std::views::iota(1,int(a.size()) - 1) | std::views::reverse) {
            for(let j in std::views::iota(i,int(a.size()) - 1)) {
                d[i][j] = std::ranges::min (
                        std::views::iota(i,j + 1) | std::views::transform([&,i,j,len = a[j + 1] - a[i - 1]](int k) {
                            return len + d[i][k - 1] + d[k + 1][j];
                        }));
            }
        }


        return d[1][a.size() - 2];

    }
};

fun main() -> signed
{
    let cuts = std::vector{ 5,6,1,4,7 };
    std::cout << Solution{}.minCost(9,cuts);

    return 0;
}