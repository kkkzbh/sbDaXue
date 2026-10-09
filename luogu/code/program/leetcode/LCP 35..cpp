

#include<bits/extc++.h>

using namespace std;

class Solution
{
public:
    int electricCarPlan(vector<vector<int>> &p, int cnt, int s, int e, vector<int> &c)
    {

#define let auto
#define in :

        let constexpr INF = std::numeric_limits<int>::max();

        let n = int(c.size());

        using node = std::pair<int, int>;
        let g = std::vector(n, std::vector<node>{});
        for(let side in p) {
            let const &A = side[0];
            let const &B = side[1];
            let const &distance = side[2];
            g[A].emplace_back(B, distance);
            g[B].emplace_back(A, distance);
        }

        let dis = std::vector(n, std::vector(cnt + 1, INF));
        dis[s][0] = 0;

        let que_cmp = [&dis,compare = std::greater{}](node x, node y) {
            let const &[v1, c1] = x;
            let const &[v2, c2] = y;
            return compare(dis[v1][c1], dis[v2][c2]);
        };
        let que = __gnu_pbds::priority_queue<node, decltype(que_cmp)>{que_cmp};
        let q = std::vector(n, std::vector(cnt + 1, decltype(que)::point_iterator{}));

        let const &range = std::views::iota;

        for(let i in range(0, n)) {
            for(let j in range(0, cnt + 1)) {
                q[i][j] = que.push({ i,j });
            }
        }

        while(not que.empty()) {

            let [it, cv] = que.top();
            que.pop();
            if(it == e) {
                return dis[it][cv];
            }
            if(cv < cnt and dis[it][cv] + c[it] < dis[it][cv + 1]) {
                dis[it][cv + 1] = dis[it][cv] + c[it];
                que.modify(q[it][cv + 1], *q[it][cv + 1]);
            }

            for(let [i, w] in g[it] | views::filter([&dis, it, cv](node p) {
                let const &[i, w] = p;
                return cv >= w and dis[it][cv] + w < dis[i][cv - w];
            })) {
                dis[i][cv - w] = dis[it][cv] + w;
                que.modify(q[i][cv - w], *q[i][cv - w]);
            }

        }

        return EOF;

    }
};