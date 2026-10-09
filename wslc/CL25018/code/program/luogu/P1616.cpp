

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>


#define fun auto
#define print(...) std::cout << std::format(__VA_ARGS__)

constexpr static int N{ 10000 + 2 };
constexpr static int N2{ 10000000 + 2 };

using int64 =long long;

struct node
{
    fun friend operator>>(std::istream& is,node& n) -> std::istream&
    {
        return is >> n.t >> n.weigh;
    }
    int t;
    int weigh;
};

int t,m;
std::array<node,N> a;
std::array<int64,N2> dp;

fun scan()
{
    std::cin >> t >> m;
    std::copy_n(std::istream_iterator<node>{ std::cin },m,a.begin() + 1);
}

fun fdp()
{
    for(int i{ 1 }; i <= m; ++i)
    {
        for(int j{ a[i].t }; j <= t;++j)
        {
            dp[j] = std::max(dp[j],dp[j - a[i].t] + a[i].weigh);
        }
    }
}

fun put()
{
    print("{}",dp[t]);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    fdp();
    put();

    return 0;
}