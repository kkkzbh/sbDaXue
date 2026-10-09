

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>


#define fun auto
#define print(...) std::cout << std::format(__VA_ARGS__)

constexpr static int N{ 2 * 10000 + 2 };

struct node
{
    fun friend operator>>(std::istream& is,node& n) -> std::istream&
    {
        return is >> n.l >> n.r;
    }
    fun friend operator<=>(node n1,node n2) = default;

    int l,r;
};

int n;
std::array<node,N> a;
std::array<std::array<int,2>,N> dp;

fun scan()
{
    std::cin >> n;
    std::copy_n(std::istream_iterator<node>{ std::cin },n,a.begin() + 1);
    std::ranges::for_each(std::views::counted(dp.begin() + 1,n),[](auto& v)
    {
        std::ranges::fill(v,-1);
    });
}

fun dfs(const int x,const int y) -> int
{
    if(x == n + 1)
    {
        return n - y;
    }
    int ret;
    if(y <= a[x].l)
    {
        if(dp[x][1] == -1)
        {
            dp[x][1] = dfs(x + 1,a[x].r) + 1;
        }
        ret = a[x].r - y + dp[x][1];
    }
    else if(y >= a[x].r)
    {
        if(dp[x][0] == -1)
        {
            dp[x][0] = dfs(x + 1,a[x].l) + 1;
        }
        ret = y - a[x].l + dp[x][0];
    }
    else
    {
        if(dp[x][1] == -1)
        {
            dp[x][1] = dfs(x + 1,a[x].r) + 1;
        }
        if(dp[x][0] == -1)
        {
            dp[x][0] = dfs(x + 1,a[x].l) + 1;
        }
        ret = std::min
                (
                        dp[x][0] + std::abs(y - a[x].r) + a[x].r - a[x].l,
                        dp[x][1] + std::abs(y - a[x].l) + a[x].r - a[x].l
                );
    }
    return ret;
}


fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    print("{}",dfs(1,1) - 1);

    return 0;
}