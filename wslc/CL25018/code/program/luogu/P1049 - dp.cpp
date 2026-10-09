

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>


#define fun auto
#define print(...) std::cout << std::format(__VA_ARGS__)

constexpr static int N{ 30 + 2 };
constexpr static int N2{ 20000 + 2 };

std::array<int,N> a;
int n,v;
std::array<std::array<int,N2>,N> dp;

fun scan()
{
    std::cin >> v >> n;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin() + 1);
}

fun fdp()
{
    for(int i{ 1 }; i <= n; ++i)
    {
        for(int j{ 1 }; j <= v; ++j)
        {
            if(j >= a[i])
            {
                dp[i][j] = std::max(dp[i - 1][j],dp[i - 1][j - a[i]] + a[i]);
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
}

fun put()
{
    print("{}",v - dp[n][v]);
}


fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    fdp();
    put();

    return 0;
}