

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>


#define fun auto
#define print(...) std::cout << std::format(__VA_ARGS__)

constexpr static int N{ 2 * 100000 + 2 };

std::array<int,N> a;
int n;
int dp,ans{ std::numeric_limits<int>::min() };

fun scan()
{
    std::cin >> n;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin() + 1 );
}

fun fdp()
{
    for(int i{ 1 }; i <= n; ++i)
    {
        dp = std::max(dp + a[i],a[i]);
        ans = std::max(ans,dp);
    }
}

fun put()
{
    print("{}",ans);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    fdp();
    put();

    return 0;
}