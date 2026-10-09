


#include<iostream>
#include<array>
#include<queue>
#include<utility>

constexpr int size{30 + 10};
constexpr std::array<std::array<int,2>,5> move{{
                                                       {},{-1,0},{0,1},{1,0},{0,-1}
                                               }};
int n;
std::array<std::array<int,size>,size> a;
std::array<std::array<int,size>,size> cp;

int st,ed;

bool isborder(int x,int y)
{
    return x == 0 || x == n + 1 || y == 0 || y == n + 1;
}

void bfs()
{
    std::queue<std::pair<int,int>> que;
    que.emplace(st,ed);
    a[st][ed] = 2;
    while(!que.empty())
    {
        auto& p = que.front();
        for(int i = 1; i <= 4;++i)
        {
            int x_ = p.first + move[i][0];
            int y_ = p.second + move[i][1];
            if(!a[x_][y_]) que.emplace(x_,y_),a[x_][y_] = 2;
        }
        que.pop();
    }
}

void bfs(int x,int y)
{
    std::queue<std::pair<int,int>> que;
    que.emplace(x,y);
    int flag = 1;
    while(!que.empty())
    {
        auto& p = que.front();
        for(int i = 1; i <= 4;++i)
        {
            int x_ = p.first + move[i][0];
            int y_ = p.second + move[i][1];
            if(isborder(x_,y_)) flag = 0;
            if(!cp[x_][y_]) cp[x_][y_] = 1,que.emplace(x_,y_);
        }
        que.pop();
    }
    if(flag) bfs();
}

int main()
{
    std::cin >> n;
    for(int i = 1; i <= n;++i)
        for(int j = 1; j <= n;++j)
            std::cin >> a[i][j];
    for(int i = 1; i <= n;i++) a[0][i] = a[i][0] = a[n + 1][i] = a[i][n+1] = 1;
    cp = a;
    for(int i = 1; i <= n;++i)
        for(int j = 1; j <= n;++j)
            if(!cp[i][j]) st = i,ed = j,bfs(i,j);
    for(int i = 1; i <= n;++i)
    {
        for(int j = 1; j <= n;++j) std::cout << a[i][j] << ' ';
        std::cout << '\n';
    }

    return 0;
}