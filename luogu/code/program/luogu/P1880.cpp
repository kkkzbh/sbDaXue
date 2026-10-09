


#include<iostream>
#include<vector>
#include<ranges>
#include<algorithm>
#include<cassert>

#define fun auto
#define let auto
#define in :


fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    using namespace std::views;
    let scan = []<typename... T>(T&... vs) { (std::cin >> ... >> vs); };
    int n;
    std::cin >> n;
    let a = std::vector(n,0);
    std::ranges::for_each(a,scan);
    a.resize(2 * n);
    std::ranges::copy_n(a.begin(),n,std::ranges::next(a.begin(),n));
    struct prefix_fn {
        explicit prefix_fn(std::vector<int>& v) : a(v.size() + 1,0) {
            for(let i in iota(0,int(v.size()))) {
                a[i + 1] = a[i] + v[i];
            }
        }
        fun operator()(int l,int r) -> int
        { return a[r] - a[l]; }
        std::vector<int> a;
    } prefix{ a };

    std::cout << std::ranges::min (
            iota(0,n) | transform([&](int i) {
                return [&,f = [&,dp = std::vector(n + 1,std::vector(n + 1,-1LL))](auto& self,int l,int r) mutable {
                    if(l + 1 == r) {
                        return 0LL;
                    }
                    let ll = l - i,rr = r - i;
                    if(dp[ll][rr] != -1) {
                        return dp[ll][rr];
                    }
                    return dp[ll][rr] = std::ranges::min (
                            iota(l + 1,r) | transform([&](int i) {
                                return self(self,l,i) + self(self,i,r) + prefix(l,i) + prefix(i,r);
                            })
                    );
                }](int i) mutable {
                    return f(f,i,i + n);
                }(i);
            })
    );
    std::cout << '\n';
    std::cout << std::ranges::max (
            iota(0,n) | transform([&](int k) {
                let dp = std::vector(n + 1,std::vector(n + 1,0LL));
                for(let l in iota(0,n - 1) | reverse) {
                    for(let r in iota(l + 2,n + 1)) {
                        dp[l][r] = std::ranges::max (
                                iota(l + 1,r) | transform([&](int i) {
#define sign k
                                    return dp[l][i] + dp[i][r] + prefix(l + sign,i + sign) + prefix(i + sign,r + sign);
                                })
                        );
                    }
                }
                return dp[0][n];
            })
    );

    return 0;
};