

#include<bits/extc++.h>

#define let auto
#define fun auto
#define in :


fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    using namespace std::ranges::views;
    let scan = []<typename T>(T& value){ std::cin >> value; };
    int n,m;
    std::cin >> n >> m;
    let pass = std::vector(m,0);
    std::ranges::for_each(pass,scan);
    std::ranges::transform(pass,pass.begin(),[](int v){ return v - 1; });
    let constexpr INF = 2147483647;
    let g = std::vector(n,std::vector(n,0)),&dis = g;
    std::ranges::for_each(g | join,scan);
    for(let k in iota(0,n)) {
        for(let i in iota(0,n)) {
            for(let j in iota(0,n)) {
                if(dis[i][k] + dis[k][j] < dis[i][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
    std::cout << [&] {
        let ans = 0LL;
        for(let i in iota(1,m)) {
            let const &from = pass[i - 1],&to = pass[i];
            ans += dis[from][to];
        }
        return ans;
    }();

    return 0;
};