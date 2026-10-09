

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>


#define fun auto
#define print(...) std::cout << std::format(__VA_ARGS__)

using int64 = long long;

constexpr static int N{ 1000 + 2 };

struct node
{
    fun friend operator>>(std::istream& is,node& n) -> std::istream&
    {
        return is >> n.lose >> n.win >> n.use;
    }
    int lose;
    int win;
    int use;
};

std::array<node,N> a;
int n,x;
std::array<int,N> dp;

fun scan()
{
    std::cin >> n >> x;
    std::copy_n(std::istream_iterator<node>{ std::cin },n,a.begin() + 1);
}

fun fdp()
{
    for(int i{ 1 }; i <= n; ++i)
    {
        for(int j{ x }; j >= 0; --j)
        {
            if(j >= a[i].use)
            {
                dp[j] = std::max(dp[j] + a[i].lose,dp[j - a[i].use] + a[i].win);
            }
            else
            {
                dp[j] += a[i].lose;
            }
        }
    }
}

fun put()
{
    print("{}",dp[x] * 5ll);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    fdp();
    put();

    return 0;
}