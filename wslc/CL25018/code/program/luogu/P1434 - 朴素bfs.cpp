

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>
#include<queue>

#define fun auto
#define print(...) std::cout << std::format(__VA_ARGS__)

constexpr static int N{ 100 + 2 };
constexpr static std::array move{ -1,0,1,0,-1 }; // 0-1 1-2 2-3 3-4 上下左右

std::array<std::array<int,N>,N> a,dp;
int r,c;

fun scan() -> void
{
    std::cin >> r >> c;
    for(int i{ 1 }; i <= r; ++i)
    {
        std::copy_n(std::istream_iterator<int>{ std::cin },c,a[i].begin() + 1);
    }
}

fun check(int i,int j) -> bool
{
    return i >= 1 and i <= r and j >= 1 and j <= c;
}

fun bfs(int sx,int sy) -> int
{
    std::queue<std::pair<int,int>> que;
    que.emplace(sx,sy);
    int level{};
    while(!que.empty())
    {
        for(int i{},cei{ static_cast<int>(que.size()) }; i != cei; ++i)
        {
            const auto [x,y]{ que.front() };
            que.pop();
            for(int k{}; k <= 3; ++k)
            {
                int mx{ x + move[k] };
                int my{ y + move[k + 1] };
                if(check(mx,my) and a[x][y] > a[mx][my])
                {
                    que.emplace(mx,my);
                }
            }
        }
        ++level;
    }
    return level;
}

fun fdp() -> void
{
    int max{ 1 };
    for(int i{ 1 }; i <= r; ++i)
    {
        for(int j{ 1 }; j <= c; ++j)
        {
            max = std::max(max,bfs(i, j));
        }
    }
    print("{}",max);
}


fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    fdp();

    return 0;
}