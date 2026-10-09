

#include<iostream>
#include<vector>
#include<algorithm>
#include<ranges>

#define fun auto
#define let auto
#define in :

using node = std::pair<int,int>;
using namespace std::views;

fun solve()
{
    let n = 5,c = 10;
    let s = std::vector{ 2,2,6,5,4 };
    let v = std::vector{ 6,3,5,4,6 };
    let dp = std::vector(n + 1,std::vector(c + 1,0));
    for(let i in iota(1,n + 1)) {
        for(let j in iota(0,c + 1)) {
            dp[i][j] = dp[i - 1][j];
            if(j >= s[i - 1]) {
                dp[i][j] = std::max(dp[i][j],dp[i - 1][j - s[i - 1]] + v[i - 1]);
            }
        }
    }
    std::cout << dp[n][c];
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    let scan = []<typename... T>(T&... vs) { (std::cin >> ... >> vs); };
    let scand = [&](auto& v) { scan(v); --v; };
    int m,n;
    std::cin >> m >> n;
    let order = std::vector(m * n,0);
    std::ranges::for_each(order,scand);
    let a = std::vector(n,std::vector(m,node{}));
    std::ranges::for_each(a | join | keys,scand);
    std::ranges::for_each(a | join | values,scan);
    for(let &vec in a) {
        std::ranges::reverse(vec);
    }
    let last = std::vector(n,0);
    let mac = std::vector(m,0);
    for(let const& v in order) {
        let const& [mi,t] = a[v].back();
        let nt = std::max(last[v],mac[mi]) + t;
        last[v] = mac[mi] = nt;
    }
    std::cout << std::ranges::max(mac) << '\n';
    solve();
};