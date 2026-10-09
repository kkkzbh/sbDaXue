

#include <bits/stdc++.h>

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto constexpr INF = std::numeric_limits<int>::max() / 2;
    auto dis = std::vector(n + 1,std::vector(m + 1,INF));
    dis[0][0] = 0;
    using node = std::pair<int,int>; // x y
    auto constexpr move = std::array{ -1,-1,1,1,-1 };
    auto constexpr dir = std::array{ 1,0,1,0 };
    auto constexpr cd = std::array{ -1,-1,0,0,-1 };
    auto g = std::vector(n,std::vector(m,0));
    for(auto i = 0; i != n; ++i) {
        for(auto j = 0; j != m; ++j) {
            char c;
            std::cin >> c;
            g[i][j] = c == '/' ? 0 : 1;
        }
    }
    auto que = std::deque<node>{};
    que.emplace_back(0,0);
    while(not que.empty()) {
        auto [x,y] = que.front();
        que.pop_front();
        for(auto i = 0; i != 4; ++i) {
            auto [nx,ny] = node{ x + move[i],y + move[i + 1] };
            if(nx < 0 or nx > n or ny < 0 or ny > m) {
                continue;
            }
            assert(x + cd[i] >= 0 and x + cd[i] < n and y + cd[i + 1] >= 0 and y + cd[i + 1] < m);
            auto d = int(g[x + cd[i]][y + cd[i + 1]] != dir[i]);
            if(dis[x][y] + d < dis[nx][ny]) {
                dis[nx][ny] = dis[x][y] + d;
                if(nx == n and ny == m) {
                    goto aans;
                }
                if(d) {
                    que.emplace_back(nx,ny);
                } else {
                    que.emplace_front(nx,ny);
                }
            }
        }
    }

    aans:
    if(dis[n][m] == INF) {
        std::cout << "NO SOLUTION\n";
        return 0;
    }
    std::cout << dis[n][m];

}