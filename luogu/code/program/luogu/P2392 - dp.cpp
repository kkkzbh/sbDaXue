

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>
#include<cmath>
#include<numeric>

#define fun auto
#define print(...) std::cout << std::format(__VA_ARGS__)

constexpr static int N{ 20 + 2 };
constexpr static int N2{ 4 + 2 };
constexpr static int N3{ 1200 + 2 };

std::array<int,N2> n;
std::array<std::array<int,N>,N2> a;
std::array<int,N3> dp;

fun scan()
{
    std::cin >> n[1] >> n[2] >> n[3] >> n[4];
    for(int i : std::views::iota(1,5))
    {
        std::copy_n(std::istream_iterator<int>{ std::cin },n[i],a[i].begin() + 1);
    }
}

fun fdp() -> int
{
    int ret{};
    for(int k : std::views::iota(1,4 + 1))
    {
        int sum{ std::accumulate(a[k].begin() + 1,a[k].begin() + 1 + n[k],0) };
        for(int i : std::views::iota(1,n[k] + 1))
        {
            for(int j : std::views::iota(std::min(a[k][i],(sum >> 1) + 1),(sum >> 1) + 1) | std::views::reverse)
            {
                dp[j] = std::max(dp[j],dp[j - a[k][i]] + a[k][i]);
            }
        }
        ret += sum - dp[sum >> 1];
        std::ranges::fill(std::views::counted(dp.begin(),(sum >> 1) + 1),0);
    }
    return ret;
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    print("{}",fdp());

    return 0;
}