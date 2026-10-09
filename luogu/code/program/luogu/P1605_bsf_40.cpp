


#include<iostream>
#include<array>
#include<queue>

constexpr int size = 5 + 3;
constexpr std::array<std::array<int,4 + 1>,4 + 1> move{{
                                                               {},{-1,0},{0,1},{1,0},{0,-1}
                                                       }};
std::array<std::array<int,size>,size> map;
int n,m;
int fx,fy,sx,sy;
int ans;

void bfs()
{
    std::queue<std::pair<int,int>> que;
    que.emplace(fx,fy);
    std::pair<int,int> &pos = que.front();
    while(!que.empty())
    {
        pos = que.front();
        if(pos.first == sx && pos.second == sy) ++ans;
        else
            for(int i = 2; i <= 3;++i)
            {
                int x = pos.first + move[i][0];
                int y = pos.second + move[i][1];
                if(!map[x][y]) que.emplace(x,y);
            }
        que.pop();
    }
}

int main()
{
    int _; std::cin >> n >> m >> _;
    std::cin >> fx >> fy >> sx >> sy;
    for(int i = 1; i <= n;++i) map[0][i] = map[i][0] = map[n + 1][i] = map[i][n + 1] = 1;
    while(_--)
    {
        int v1,v2; std::cin >> v1 >> v2;
        map[v1][v2] = 1;
    }
    bfs();
    std::cout << ans;

    return 0;
}