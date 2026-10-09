

#include<bits/stdc++.h>

using namespace std;

#define fun auto
#define let auto
#define in :
#define print(...) std::cout << std::format(__VA_ARGS__)
#define println(...) print(__VA_ARGS__) << '\n'

using int64 = long long;

class Solution {
public:

    let constexpr static MOD = 1000000000 + 7;

    int cuttingBamboo(int len)
    {
        if(len == 2 or len == 3) {
            return len - 1;
        }
        let pow = [](int64 num,int p) {
            let ret = 1LL;
            for(; p; p >>= 1) {
                if(p & 1) {
                    ret *= num;
                    ret %= MOD;
                }
                num *= num;
                num %= MOD;
            }
            return int(ret);
        };

        if(let r = len % 3; not r) {
            return pow(3,len / 3);
        } else if(r == 1) {
            return int((pow(3,len / 3 - 1) * 4LL) % MOD);
        } else {
            return int((pow(3,len / 3) * 2LL) % MOD);
        }

    }
};
