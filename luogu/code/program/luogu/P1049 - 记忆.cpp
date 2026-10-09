

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

fun dfs(int i,int val) -> int
{
    if(i == n + 1)
    {
        return val;
    }
    if(dp[i][val])
    {
        return dp[i][val];
    }
    int m1{ 2147483647 },m2;
    if(val >= a[i])
    {
        m1 = dfs(i + 1,val - a[i]);
    }
    m2 = dfs(i + 1,val);
    return dp[i][val] = std::min(m1,m2);
}

fun put()
{
    print("{}",dp[n][v]);
}


fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    print("{}",dfs(1,v));

    return 0;
}