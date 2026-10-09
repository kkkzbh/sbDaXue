

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

constexpr static int N{ 2 * 10000 + 2 };

struct node
{
    fun friend operator>>(std::istream& is,node& n) -> std::istream&
    {
        return is >> n.l >> n.r;
    }
    int l,r;
};

int n;
std::array<node,N> a;
std::array<std::array<int,2>,N> dp;

fun scan()
{
    std::cin >> n;
    std::copy_n(std::istream_iterator<node>{ std::cin },n,a.begin() + 1);
}

fun fdp()
{
    a[0].l = a[0].r = 1;
    a[n].r = n;

    for(int i{ 1 }; i <= n; ++i)
    {
        dp[i][0] = std::min
                (
                        dp[i - 1][0] + std::abs(a[i].r - a[i - 1].l) + a[i].r - a[i].l + 1,
                        dp[i - 1][1] + std::abs(a[i].r - a[i - 1].r) + a[i].r - a[i].l + 1
                );
        dp[i][1] = std::min
                (
                        dp[i - 1][0] + std::abs(a[i].l - a[i - 1].l) + a[i].r - a[i].l + 1,
                        dp[i - 1][1] + std::abs(a[i].l - a[i - 1].r) + a[i].r - a[i].l + 1
                );
    }
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    fdp();
    print("{}",dp[n][1] - 1);

    return 0;
}