

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

constexpr static int N2{ 100 * 100 + 2 };

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



fun fdp() -> void
{
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,
            decltype([](const auto p1,const auto p2)
            {
                return a[p1.first][p1.second] > a[p2.first][p2.second];
            })> que;
    for(int i{ 1 }; i <= r; ++i)
    {
        for(int j{ 1 }; j <= c; ++j)
        {
            que.emplace(i,j);
        }
    }
    std::ranges::for_each(std::views::counted(dp.begin() + 1,r),[](auto& v){ std::ranges::fill(std::views::counted(v.begin() + 1,c),1); });
    int ans{ 1 };
    while(!que.empty())
    {
        const auto [x,y]{ que.top() };
        que.pop();
        for(int k{}; k <= 3; ++k)
        {
            int mx{ x + move[k] };
            int my{ y + move[k + 1] };
            if(check(mx,my) and a[x][y] > a[mx][my])
            {
                ans = std::max(ans,dp[x][y] = std::max(dp[x][y],dp[mx][my] + 1));
            }
        }
    }
    print("{}",ans);
}


fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    fdp();

    return 0;
}