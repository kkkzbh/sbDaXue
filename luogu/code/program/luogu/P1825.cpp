

#include<iostream>
#include<array>
#include<utility>
#include<queue>

constexpr int size = 300 + 10;
constexpr std::array<std::array<int,2>,5> move{{
                                                       {},{-1,0},{0,1},{1,0},{0,-1}
                                               }};
constexpr std::pair<int,int> null;

int n,m;
std::array<std::array<char,size>,size> a;
std::array<std::array<std::pair<int,int>,size>,size> t; //传送数组
std::array<std::pair<int,int>,'Z' - 'A' + 1> set;   //记录字母是否第一次出现
std::pair<int,int> destination;

inline int hash(int c) { return c - 'A'; }

int bfs(std::pair<int,int>& start)
{
    std::queue<std::pair<int,int>> que;
    a[start.first][start.second] = '#';
    if(t[start.first][start.second] != null) que.push(t[start.first][start.second]);
    else que.push(start);
    int count = 0;
    auto* last = &que.front();
    while(!que.empty())
    {
        auto& p = que.front();
        if(p == destination) break;
        for(int i = 1; i <= 4;++i)
        {
            int x = p.first + move[i][0];
            int y = p.second + move[i][1];
            auto& ptr = t[x][y];
            if(ptr != null && a[x][y] != '#')
            {
                que.push(ptr);
                a[x][y] = '#';
            }
            else if(a[x][y] != '#')
            {
                que.emplace(x,y);
                a[x][y] = '#';
            }
        }
        if(&que.front() == last)
        {
            last = &que.back();
            ++count;
        }
        que.pop();
    }
    return count;
}

int main()
{
    std::pair<int,int> start;
    std::cin >> n >> m;
    for(int i = 1; i <= n;++i) a[i][0] = a[i][m + 1] = '#';
    for(int i = 1; i <= m;++i) a[0][i] = a[n + 1][i] = '#';
    for(int i = 1; i <= n;++i)
        for(int j = 1; j <= m;++j)
        {
            std::cin >> a[i][j];
            if(isalpha(a[i][j]))
            {
                if (set[hash(a[i][j])] == null) set[hash(a[i][j])].first = i, set[hash(a[i][j])].second = j;
                else
                {
                    auto &tmp = set[hash(a[i][j])];
                    t[i][j].first = tmp.first;
                    t[i][j].second = tmp.second;
                    t[tmp.first][tmp.second].first = i;
                    t[tmp.first][tmp.second].second = j;
                }
            }
            else if(a[i][j] == '@') start.first = i,start.second = j;
            else if(a[i][j] == '=') destination.first = i,destination.second = j;
        }
    std::cout << bfs(start);


    return 0;
}