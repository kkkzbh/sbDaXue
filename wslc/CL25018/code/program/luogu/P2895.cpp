

#include<iostream>
#include<array>
#include<queue>
#include<utility>
#include<algorithm>

constexpr int size = 300 + 10;
constexpr std::array<std::array<int,3>,5> move{{
                                                       {},{1,0},{0,1},{-1,0},{0,-1}
                                               }};
constexpr int floor = 1000 + 1;

std::array<std::array<int,size>,size> a;
int dis;
int ans{-1};

inline bool isborder(int x,int y)
{
    return x < 1 || y < 1;
}

inline bool isget(int x,int y)
{
    return dis < a[x][y] - 1;
}

void bfs(int x,int y)
{
    std::queue<std::pair<int,int>> que;
    que.emplace(x,y);
    auto* last = &que.front();
    decltype(last) now = nullptr;
    while(!que.empty())
    {
        int _x = que.front().first;
        int _y = que.front().second;
        if(a[_x][_y] == floor)
        {
            ans = dis;
            break;
        }
        for(int i = 1; i <= 4;++i)
        {
            int X = _x + move[i][0],Y = _y + move[i][1];
            if(isget(X,Y)) que.emplace(X,Y),now = &que.back(),a[X][Y] = a[X][Y] == floor ? floor : 0;
        }
        if(&que.front() == last)
        {
            last = now;
            ++dis;
        }
        que.pop();
    }
}

int main()
{
    int n; std::cin >> n;
    int v1,v2,t;
    for(int i = 1; i <= 302;++i) for(int j = 1; j <= 302;++j) a[i][j] = floor;
    for(int i = 1; i <= n;++i)
    {
        std::cin >> v1 >> v2 >> t; ++v1,++v2;
        for(int j = 0; j <= 4;++j)
        {
            int x = v1 + move[j][0],y = v2 + move[j][1];
            if(!isborder(x,y)) a[x][y] = std::min(t,a[x][y]);
        }
    }
    bfs(1,1);
    std::cout << ans;

    return 0;
}
