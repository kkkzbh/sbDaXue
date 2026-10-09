

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

#if __cplusplus >= 202002L
using namespace std::ranges::views;
#endif

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();

enum { luogu,codeforces };
let constexpr check_ = codeforces;

class Solution
{
public:
    int ladderLength(std::string &s1, std::string &s2, std::vector<std::string> &a)
    {
        let vis = std::vector(a.size(), false);
        let que = std::deque<int>{};

        let ok = [](const auto &s, const auto &ps) {
            let flag = false;
            for(let i in std::views::iota(0, int(ps.size()))) {
                if(s[i] != ps[i]) {
                    if(flag) {
                        return false;
                    } else {
                        flag = true;
                    }
                }
            }
            return flag;
        };

        for(let i in std::views::iota(0, int(a.size()))) {
            if(ok(s1, a[i])) {
                que.push_back(i);
                vis[i] = true;
            }
        }

        let bfs = [&] { ;
            let ans = 2;
            while(!que.empty()) {
                for(let i in std::views::iota(0, int(que.size()))) {
                    let const &it = a[que.front()];
                    que.pop_front();
                    if(it == s2) {
                        return ans;
                    }
                    for(let j in std::views::iota(0, int(a.size())) |
                                 std::views::filter([&](int i) { return !vis[i]; })) {
                        if(ok(it, a[j])) {
                            que.push_back(j);
                            vis[j] = true;
                        }
                    }
                }
                ++ans;
            }
            return 0;
        };

        return bfs();

    }
};

