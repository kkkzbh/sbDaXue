

#include<bits/stdc++.h>

#define fun auto
#define let auto
#define in :

struct rep
{
    int basic;
    int count;
    std::vector<int> goods;
};

fun main() -> signed
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);

    int n,m,v;
    std::cin >> n >> m >> v;

    let a = std::vector(n,rep{});
    for(let &[b,c,g] in a) {
        std::cin >> b >> c;
    }
    for(let i = 0; i != m; ++i) {
        int t,profit;
        std::cin >> profit >> t;
        a[t].goods.push_back(profit);
    }
    for(let &[b,c,g] in a) {
        std::sort(g.rbegin(),g.rend());
    }

    let prefix = std::vector(n,std::vector<int>{ 0 });
    let sum = [&](int l,int r,int i) {
        return prefix[i][r + 1] - prefix[i][l];
    };

    for(let i = 0; i != n; ++i) {
        let &vec = a[i].goods;
        let &pre = prefix[i];
        for(let val in vec) {
            pre.push_back(pre.back() + val);
        }
    }

    /*
     *  dp[i][j] 前i个仓库 有j元现金可得的最大利润
     *  dp[i][j] = max -> dp[i - 1][j] | dp[i - 1][j - (kc + b)] + sum(0,k - 1);
     *
     */

    let dp = std::vector(v + 1,0);

    for(let i = 1; i <= n; ++i) {
        for(let j = v; j >= 1; --j) {
            for(let k = 1; k != prefix[i - 1].size() and (k * a[i - 1].count + a[i - 1].basic) <= j; ++k) {
                dp[j] = std::max(dp[j],dp[j - (k * a[i - 1].count + a[i - 1].basic)] + sum(0,k - 1,i - 1) - (k * a[i - 1].count + a[i - 1].basic));
            }
        }
    }

    let &ans = dp;
    let it = std::find_if(ans.begin(),ans.end(),[v](int val){ return val >= v; });
    std::cout << std::distance(ans.begin(),it);


    return 0;
};