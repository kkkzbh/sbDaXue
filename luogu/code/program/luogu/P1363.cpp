


#include<iostream>
#include<array>
#include<utility>
#include<cmath>

constexpr int M_size{ 1500 + 2 };
constexpr std::pair<int,int> null{ 0,0 };
constexpr std::array<std::array<int,2>,5> move{{
                                                       {},{0,1},{1,0},{0,-1},{-1,0}
                                               }};
constexpr char ans[][5]{"No\n","Yes\n"};

int n,m;
std::array<std::array<char,M_size>,M_size> a;
std::array<std::array<std::pair<int,int>,M_size>,M_size> vis;
std::pair<int,int> st;

#define kxm (((kx % n) + n - 1) % n + 1)  //无限+n 突破负数与正数的区别
#define kym (((ky % m) + m - 1) % m + 1)

bool dfs(int i,int j)
{
    for(int k{ 1 }; k <= 4; ++k)
    {
        int kx = i + move[k][0];
        int ky = j + move[k][1];
        int M_kx = kxm;
        int M_ky = kym;
        if(a[M_kx][M_ky] != '#')
        {
            if(vis[M_kx][M_ky] == null)
            {
                vis[M_kx][M_ky] = std::make_pair(kx,ky);
                if(dfs(kx, ky))
                    return true;
                //vis[M_kx][M_ky] = null;
            }
            else if(vis[M_kx][M_ky] != std::make_pair(kx,ky))
                return true;
        }
    }
    return false;
}

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
//    for(int i{}; i != M_size; ++i)
//        a[0][i] = a[i][0] = a[M_size - 1][i] = a[i][M_size - 1] = '#';
    while(std::cin >> n)
    {
        std::cin >> m;
        for(int i{ 1 }; i <= n; ++i)
            for(int j{ 1 }; j <= m; ++j)
            {
                std::cin >> a[i][j];
                if(a[i][j] == 'S')
                    st = std::make_pair(i,j);
            }
        vis[st.first][st.second] = st;
        std::cout << ans[dfs(st.first,st.second)];
        for(int i{ 1 }; i <= n; ++i)
            for(int j{ 1 }; j <= m; ++j)
                vis[i][j] = std::make_pair(0,0);
    }


    return 0;
}