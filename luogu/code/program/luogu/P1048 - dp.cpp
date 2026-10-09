

#include<iostream>
#include<format>
#include<array>
#include<algorithm>
#include<iterator>
#include<ranges>

#define fun auto
#define print(...) std::cout << std::format(__VA_ARGS__)

constexpr static int N1{ 1000 + 2 };
constexpr static int N2{ 100 + 2 };

struct node
{
    fun friend operator>>(std::istream& is,node& n) -> std::istream&
    {
        return is >> n.t >> n.weigh;
    }
    int t;
    int weigh;
};

std::array<node,N2> a;
int t,n;
std::array<std::array<int,N1>,N2> dp;

fun fdp() -> void
{
    for(int i{ 1 }; i <= n; ++i)
    {
        for(int j{ 1 }; j <= t; ++j)
        {
            if(j >= a[i].t)
            {
                dp[i][j] = std::max(dp[i - 1][j],dp[i - 1][j - a[i].t] + a[i].weigh);
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> t >> n;
    std::copy_n(std::istream_iterator<node>{ std::cin },n,a.begin() + 1);
    fdp();
    print("{:d}",dp[n][t]);

    return 0;
}