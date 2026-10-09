

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>
#include<bitset>

#define fun auto
#define print(...) std::cout << std::format(__VA_ARGS__)

constexpr static int N{ 100 + 2 };
constexpr static std::array move{ -1,0,1,0,-1 }; // 0-1 1-2 2-3 3-4 上下左右
constexpr static bool debug{  };

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

fun dfs(int i,int j) -> void
{
    for(int k{}; k <= 3; ++k)
    {
        int mi{ i + move[k] };
        int mj{ j + move[k + 1] };
        if(check(mi,mj) and a[i][j] < a[mi][mj])
        {
            if(!dp[mi][mj] or dp[i][j] + 1 > dp[mi][mj])
            {
                dp[mi][mj] = dp[i][j] + 1;
                dfs(mi,mj);
            }
        }
    }
}

fun fdp() -> void
{
    int min{ std::numeric_limits<int>::max() };
    for(int i{ 1 }; i <= r; ++i)
    {
        min = std::min(min,*std::ranges::min_element(a[i] | std::views::drop(1) | std::views::take(c)));
    }

    int max{ std::numeric_limits<int>::min() };
    for(int i{ 1 }; i <= r; ++i)
    {
        for(int j{ 1 }; j <= c; ++j)
        {
            dp[i][j] = 1;
            dfs(i, j);
            for (int k{1}; k <= r; ++k)
            {
                max = std::max(max, *std::ranges::max_element(std::views::counted(dp[k].begin() + 1, c)));
                std::ranges::fill(std::views::counted(dp[k].begin() + 1, c), 0);
            }
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