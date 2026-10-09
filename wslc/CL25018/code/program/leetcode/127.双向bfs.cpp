

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

class Solution {
public:
    int ladderLength(std::string& s1, std::string& s2, std::vector<std::string>& a)
    {

        let ok = [](const std::string& s,const std::string& ps) {
            let cnt = 0;
            for(let i = 0; i != int(s.size()) and cnt <= 1; ++i) {
                cnt += s[i] != ps[i];
            }
            return cnt == 1;
        };

        let lrbfs = [&](int l,int r) {

            let lque = std::deque<int>{};
            let lset = std::unordered_set<int>{};

            let rque = std::deque<int>{};
            let rset = std::unordered_set<int>{};

            lque.push_back(l);
            lset.insert(l);

            rque.push_back(r);
            rset.insert(r);

            let level = 2;
            while(!lque.empty() or !rque.empty()) {
                let flag = !lque.empty();
                for(let i in std::views::iota(0,int(lque.size()))) {
                    let it = lque.front();
                    lque.pop_front();
                    for(let j in std::views::iota(0,int(a.size())) | std::views::filter([&](int i) { return !lset.contains(i); })) {
                        if(ok(a[it],a[j])) {
                            if(rset.contains(j)) {
                                return level;
                            }
                            lset.insert(j);
                            lque.push_back(j);
                        }
                    }
                }
                if(flag) {
                    ++level;
                }
                flag = !rque.empty();
                for(let i in std::views::iota(0,int(rque.size()))) {
                    let it = rque.front();
                    rque.pop_front();
                    for(let j in std::views::iota(0,int(a.size())) | std::views::filter([&](int i) { return !rset.contains(i); })) {
                        if(ok(a[it],a[j])) {
                            if(lset.contains(j)) {
                                return level;
                            }
                            rset.insert(j);
                            rque.push_back(j);
                        }
                    }
                }
                if(flag) {
                    ++level;
                }
            }
            return 0;
        };

        let l = int(std::distance(a.begin(),std::ranges::find(a,s1)));
        if(l == a.size()) {
            a.push_back(std::move(s1));
        }
        let r = int(std::distance(a.begin(), std::ranges::find(a, s2)));
        if(r == a.size()) {
            return 0;
        }
        return lrbfs(l,r);

    }
};

