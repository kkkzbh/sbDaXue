

#include<bits/extc++.h>

#define fun auto
#define let auto
#define in :

fun solve()
{
    int n;
    std::cin >> n;
    let scan = []<typename... T>(T&... vs){ (std::cin >> ... >> vs); };
    let a = std::vector(n,0);
    std::ranges::for_each(a,scan);
    if(n == 1 or n == 2) {
        std::println("{}",-1);
        return;
    }
    std::ranges::sort(a);
    let mid = a[n / 2];
    let sum = std::reduce(a.begin(),a.end(),0LL);

    //  mid < ave / 2
    //  ave = sum / n
    //  ave > 2 * mid
    //  sum / n > 2 * mid
    //  sum > 2 * mid * n
    //  sum + x > 2 * mid * n
    //  x > 2 * mid * n - sum
    //  x = 2 * mid * n - sum + 1

    let ans = 2LL * mid * n - sum + 1;
    std::println("{}",std::max(ans,0LL));

};


fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while(t--) {
        std::invoke(solve);
    }


    return 0;
};