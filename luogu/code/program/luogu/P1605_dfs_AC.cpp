


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

void dfs(int x,int y)
{
    if(x == sx && y == sy)
    {
        ++ans;
        return;
    }
    for(int i = 1; i <= 4;++i)
    {
        int x_ = x + move[i][0];
        int y_ = y + move[i][1];
        if(!map[x_][y_])
        {
            map[x_][y_] = 1;
            dfs(x_,y_);
            map[x_][y_] = 0;
        }
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
    map[fx][fy] = 1;
    dfs(fx,fy);
    std::cout << ans;

    return 0;
}