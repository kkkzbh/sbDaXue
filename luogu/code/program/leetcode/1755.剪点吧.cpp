

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

enum { luogu,codeforces };
let constexpr check_ = codeforces;

class Solution {
public:
    int minAbsDifference(vector<int>& a, int tar)
    {

        let min = 0,max = 0;
        for(let v in a) {
            if(v >= 0) {
                max += v;
            } else {
                min += v;
            }
        }
        if(tar >= max) {
            return tar - max;
        }
        if(tar < min) {
            return min - tar;
        }

        std::ranges::sort(a);

        return [&,tar,f = [&](auto& self,int i,int bound,int val,auto& ans) {
            if(i == bound) {
                ans.push_back(val);
                return;
            }
            let cnt = int(std::distance(a.begin() + i,std::find_if(a.begin() + i,a.begin() + bound,[kv = a[i]](int val){ return val != kv; })));
            for(let k = 0,it = cnt + i; k <= cnt; ++k,val += a[i]) {
                self(self,it,bound,val,ans);
            }
        }]() {
            let n = int(a.size());
            let mid = n / 2;

            let lans = std::vector<int>{},rans = lans;

            f(f,0,mid,0,lans);
            f(f,mid,n,0,rans);

            std::ranges::sort(rans);

            let bs = [&,ok = [tar](int b,int va){ return b + va >= tar; }](int l,int r,int va) {
                while(l != r) {
                    let mid = (l + r) / 2;
                    if(ok(rans[mid],va)) {
                        r = mid;
                    } else {
                        l = mid + 1;
                    }
                }
                return l;
            };

            let ans = INF;
            for(let v in lans) {
                let it = bs(0,int(rans.size()),v);
                if(it != int(rans.size())) {
                    ans = std::ranges::min(ans, v + rans[it] - tar);
                }
                if(it) {
                    ans = std::ranges::min(ans,tar - v - rans[it - 1]);
                }
            }

            return ans;
        }();

    }
};