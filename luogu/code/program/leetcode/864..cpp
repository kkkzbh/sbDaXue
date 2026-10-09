

#include<bits/extc++.h>

#define fun auto
#define let auto
#define in :

using namespace std;

class Solution {
public:

    int shortestPathAllKeys(vector<string>& a) // NOLINT
    {

        enum {
            pos = '.',
            wall = '#',
            st = '@',
        };

        let n = int(a.size()),m = int(a[0].size());

        using node = std::pair<int,int>;

        node start;
        let cnt = 0;
        for(let i in views::iota(0,n)) {
            for(let j in views::iota(0,m)) {
                if(a[i][j] == st) {
                    start = { i,j };
                } else if(std::islower(a[i][j])) {
                    ++cnt;
                }
            }
        }

        let bfs = [cnt](node start,auto& grid) {

            let &[sx,sy] = start;
            let &a = grid;
            let n = int(a.size()),m = int(a[0].size());
            using state = int;

            using point = std::tuple<int,int,state>;

            let que = std::queue<point>{};
            let empty = state{};
            que.emplace(sx,sy,empty);

            let constexpr move = std::array {
                    -1,0,1,0,-1
            };

            let vis = std::vector(n,std::vector(m,std::vector(1 << cnt,false)));
            vis[sx][sy][empty] = true;
            let ret = 0;
            let win = (1 << cnt) - 1;
            while(not que.empty()) {
                for(let k in views::iota(0,int(que.size()))) {
                    let const [x, y, sta] = que.front();
                    que.pop();
                    //std::print("{},{} | ",x,y);
                    if(sta == win) {
                        return ret;
                    }
                    for(let i in views::iota(0, 4)) {
                        let mx = x + move[i], my = y + move[i + 1];
                        if((mx < 0 or mx >= n or my < 0 or my >= m) or a[mx][my] == wall) {
                            continue;
                        }
                        if(let c = a[mx][my]; std::islower(c)) {
                            let _ = sta | (1 << (c - 'a'));
                            if(vis[mx][my][_]) {
                                continue;
                            }
                            que.emplace(mx, my, _);
                            vis[mx][my][_] = true;
                        } else if(not std::isupper(c) or sta & (1 << (c - 'A'))) {
                            if(vis[mx][my][sta]) {
                                continue;
                            }
                            que.emplace(mx, my, sta);
                            vis[mx][my][sta] = true;
                        }
                    }
                }
                //std::println();
                ++ret;
            }
            return -1;
        };

        return bfs(start,a);

    }


};

fun main() -> int
{
    let _ = std::vector{ std::string{ "@.a.." },std::string{ "###.#" }, std::string{ "b.A.B" } };
    std::cout << Solution{}.shortestPathAllKeys(_);
}