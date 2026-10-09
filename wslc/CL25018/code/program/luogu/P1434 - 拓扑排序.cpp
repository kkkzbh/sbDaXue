

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
int n;

std::array<std::vector<int>,N2> g;
std::array<int,N2> ind;

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

fun cast(int i,int j) -> int
{
    return (i - 1) * c + j;
}

fun create() -> void
{
    n = r * c;
    for(int i{ 1 }; i <= r; ++i)
    {
        for(int j{ 1 }; j <= c; ++j)
        {
            for(int k{}; k <= 3; ++k)
            {
                int mx{ i + move[k] };
                int my{ j + move[k + 1] };
                if(check(mx,my) and a[i][j] > a[mx][my])
                {
                    int v{ cast(mx,my) };
                    g[cast(i,j)].push_back(v);
                    ++ind[v];
                }
            }
        }
    }
}

fun top_sort() -> int
{
    std::queue<int> que;
    for(int i{ 1 }; i <= n; ++i)
    {
        if(!ind[i])
        {
            que.push(i);
        }
    }
    int level{};
    while(!que.empty())
    {
        ++level;
        for(int i{},cei{ static_cast<int>(que.size()) }; i != cei; ++i)
        {
            int tp{ que.front() };
            que.pop();
            for(const int it : g[tp])
            {
                if(!--ind[it])
                {
                    que.push(it);
                }
            }
        }
    }
    return level;
}

fun fdp() -> void
{
    print("{}",top_sort());
}


fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    create();
    fdp();

    return 0;
}