


#include<iostream>
#include<array>
#include<queue>
#include<utility>
#include<algorithm>

constexpr int size = 400 + 10;
constexpr int mv = 8 + 1;

std::array<std::array<int,size>,size> a;
int n,m;
int x,y;

constexpr std::array<std::array<int,mv>,8 + 1> move{{
                                                            {},{-1,-2},{-2,-1},{-2,1},{-1,2},{1,-2},{2,-1},{2,1},{1,2}
                                                    }};

inline bool isvalid(int x,int y)
{
    return x >= 1 && x <= n && y >= 1 && y <= m && a[x][y] == -1;
}

void bfs(int x,int y)
{
    std::queue<std::pair<int,int>> que;
    que.emplace(x,y);
    while(!que.empty())
    {
        auto& tmp = que.front();
        for(int i = 1;i != mv;++i)
        {
            int __a = tmp.first + move[i][0];
            int __b = tmp.second + move[i][1];
            if(isvalid(__a,__b)) que.emplace(__a,__b),a[__a][__b] = a[tmp.first][tmp.second] + 1;
        }
        que.pop();
    }
}

int main()
{

    std::cin >> n >> m >> x >> y;
    for(int i = 1; i <= n;++i)
        for(int j = 1; j <= m;++j) a[i][j] = -1;
    a[x][y] = 0;
    bfs(x,y);
    std::for_each_n(a.begin() + 1,n,[](const std::array<int,size>& arr) -> void
    {
        std::for_each_n(arr.begin() + 1,m,[](int val) -> void
        {
            std::cout << val << ' ';
        });
        std::cout << '\n';
    });

    return 0;
}




