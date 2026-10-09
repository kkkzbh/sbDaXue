

#include<bits/extc++.h>

#define fun auto
#define let auto
#define in :

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    using namespace std::views;
    int n;
    std::cin >> n;
    let a = std::vector(n,0);
    let scan = []<typename... T>(T&... vs) { (std::cin >> ... >> vs); };
    std::ranges::for_each(a,scan);
    struct prefix_fn {
        explicit prefix_fn(std::vector<int>& v) : a(v.size() + 1,0)
        {
            for(let i in iota(0,int(v.size()))) {
                a[i + 1] = a[i] + v[i];
            }
        }
        fun operator()(int l,int r) -> int
        { return a[r] - a[l]; }
        std::vector<int> a;
    } prefix{ a } ;
    std::cout << [&,f = [&,dp = std::vector(n + 1,std::vector(n + 1,-1LL))](auto& self,int l,int r) mutable {
        if(l + 1 == r) {
            return 0LL;
        }
        if(l + 2 == r) {
            return 0LL + a[l] + a[l + 1];
        }
        if(dp[l][r] != -1 ){
            return dp[l][r];
        }
        return dp[l][r] = std::ranges::min (
                iota(l + 1,r) | transform([&](int i) {
                    return self(self,l,i) + self(self,i,r) + prefix(l,i) + prefix(i,r);
                })
        );
    }] mutable {
        let ret = f(f,0,n);
        return ret;
    }();

    return 0;
};