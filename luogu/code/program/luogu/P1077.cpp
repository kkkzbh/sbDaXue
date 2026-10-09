

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>


#define fun auto
#define print(...) std::cout << std::format(__VA_ARGS__)

constexpr static int N{ 100 + 2 };
constexpr static int MOD{ 1000000 + 7 };

int n,m;
std::array<int,N> a;
std::array<std::array<int,N>,N> dp;

fun scan()
{
    std::cin >> n >> m;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin() + 1);
}

fun dfs(int i,int k) -> int
{
    if(k > m)   // 剪枝
    {
        return 0;
    }
    if(i == n + 1)  // 递归停止
    {
        return k == m;
    }
    if(dp[i][k])    // 记忆
    {
        return dp[i][k];
    }
    int ret{};
    for(int j{}; j <= a[i]; ++j)
    {
        ret = (ret + dfs(i + 1, k + j)) % MOD;
    }

    return dp[i][k] = ret;
}

fun put()
{
    print("{}",dp[1][0]);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    dfs(1,0);
    put();
    int arr[10]{};
    int i{  static_cast<int>(double{ 2 } + int{ 3 }) };

    return 0;
}