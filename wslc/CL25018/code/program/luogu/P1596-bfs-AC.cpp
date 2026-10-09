

#include<iostream>
#include<array>
#include<queue>
#include<utility>

constexpr int size = 100 + 20;
constexpr std::array<std::array<int,3>,9> move{{
                                                       {},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}
                                               }};

int n,m;
std::array<std::array<char,size>,size> a;
int cnt;

void bfs(int x,int y)
{
    std::queue<std::pair<int,int>> que;
    que.emplace(x,y);
    a[x][y] = '.';
    while(!que.empty())
    {
        auto& p = que.front();
        for(int i = 1; i <= 8;++i)
        {
            int x_ = p.first + move[i][0];
            int y_ = p.second + move[i][1];
            if(a[x_][y_] == 'W') que.emplace(x_,y_),a[x_][y_] = '.';
        }
        que.pop();
    }
}

int main()
{
    std::cin >> n >> m;
    for(int i = 1; i <= n;++i)
        for(int j = 1; j <= m;++j)
            std::cin >> a[i][j];
    for(int i = 0; i <= n + 1;++i) a[i][0] = a[i][m + 1] = '.';
    for(int i = 0; i <= m + 1;++i) a[0][i] = a[n + 1][i] = '.';
    for(int i = 1; i <= n;++i)
        for(int j = 1; j <= m;++j)
            if(a[i][j] == 'W') bfs(i,j),++cnt;
    std::cout << cnt;

    return 0;
}