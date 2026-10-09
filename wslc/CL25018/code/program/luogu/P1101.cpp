


#include<iostream>
#include<array>

constexpr int size = 100 + 20;
constexpr int len = 8;
constexpr std::array<std::array<int,3>,9> move{{
    {},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}
}};
constexpr char str[]{"\0yizhong"};

int n;
std::array<std::array<char,size>,size> a;
std::array<std::array<char,size>,size> ans;
int start,end;
int x,y;

void dfs(int i,int dirction)
{
    if(i == len)
    {
        int st = start;
        int ed = end;
        for(int _ = 1; _ != len;++_)
        {
            ans[st][ed] = str[_];
            st += move[dirction][0];
            ed += move[dirction][1];
        }
    }
    if(str[i] == a[x][y])
    {
        x += move[dirction][0];
        y += move[dirction][1];
        dfs(i + 1,dirction);
    }
}

void dfs()
{
    for(int i = 1; i <= 8;++i)
    {
        x = start + move[i][0];
        y = end + move[i][1];
        dfs(2,i);
    }
}

int main()
{
    std::cin >> n;
    for(int i = 1; i <= n;++i)
        for(int j = 1; j <= n;++j)
        {
            std::cin >> a[i][j];
            ans[i][j] = '*';
        }
    for(int i = 1; i <= n;++i)
        for(int j = 1; j <= n;++j)
            if(a[i][j] == 'y')
            {
                start = i,end = j;
                dfs();
            }
    for(int i = 1; i <= n;++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            std::cout << ans[i][j];
        }
        std::cout << '\n';
    }

    return 0;
}