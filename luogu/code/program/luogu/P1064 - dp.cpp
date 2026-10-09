

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>
#include<cmath>

#define fun auto
#define print(...) std::cout << std::format(__VA_ARGS__)

constexpr static int N{ 32 * 10000 + 2 };
constexpr static int N2{ 60 + 2 };

struct node
{
    fun friend operator>>(std::istream& is,node& n) -> std::istream&
    {
        return is >> n.val >> n.weight >> n.it;
    }
    int val;
    int weight;
    int it;
};

int n,m;
std::array<node,N2> a;
std::array<std::vector<std::pair<int,int>>,N2> g;
std::array<int,N> dp;

fun scan()
{
    std::cin >> n >> m;
    std::copy_n(std::istream_iterator<node>{ std::cin },m,a.begin() + 1);
    std::ranges::for_each(std::views::iota(1,m + 1),[](int i)
    {
        if(a[i].it)
        {
            g[a[i].it].emplace_back(a[i].val,a[i].weight);
        }
    });
}

fun fdp()
{
    for(int i : std::views::iota(1,m + 1) | std::views::filter([](int i){ return !a[i].it; }))
    {
        for(int j : std::views::iota(a[i].val,n + 1) | std::views::reverse)
        {
            dp[j] = std::max(dp[j],dp[j - a[i].val] + a[i].val * a[i].weight);
            int k{ j - a[i].val };
            if(g[i].size() > 0 and k >= g[i][0].first)
            {
                dp[j] = std::max(dp[j],dp[k - g[i][0].first] + a[i].val * a[i].weight + g[i][0].first * g[i][0].second);
            }
            if(g[i].size() > 1 and k >= g[i][1].first)
            {
                dp[j] = std::max(dp[j],dp[k - g[i][1].first] + a[i].val * a[i].weight + g[i][1].first * g[i][1].second);
            }
            if(g[i].size() > 1 and k >= g[i][0].first + g[i][1].first)
            {
                dp[j] = std::max(dp[j],dp[k - g[i][0].first - g[i][1].first] + a[i].val * a[i].weight + g[i][0].first * g[i][0].second + g[i][1].first * g[i][1].second);
            }
        }
    }
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    fdp();
    print("{}",dp[n]);

    return 0;
}