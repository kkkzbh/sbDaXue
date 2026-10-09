

#include<iostream>
#include<array>

constexpr int size = 100 + 20;
constexpr std::array<std::array<int,3>,9> move{{
                                                       {},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}
                                               }};

int n,m;
std::array<std::array<char,size>,size> a;
int cnt;

void dfs(int x,int y)
{
    a[x][y] =  '.';
    for(int i = 1; i <= 8;++i)
    {
        int x_ = x + move[i][0];
        int y_ = y + move[i][1];
        if(a[x_][y_] == 'W') dfs(x_,y_);
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
            if(a[i][j] == 'W') dfs(i,j),++cnt;
    std::cout << cnt;

    return 0;
}