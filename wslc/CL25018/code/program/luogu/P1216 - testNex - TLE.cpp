

#include<iostream>
#include<format>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>
#include<array>

#define fun auto
#define var auto

#define print(...) std::cout << std::format(__VA_ARGS__)

var dp = std::array<std::array<int,100 + 2>,1000 + 2>{};
auto init = []{ std::ranges::for_each(dp,[](var& a){ a.fill(-1); }); return char{}; }();

fun dfs(int r,int i,int v,int n,const var& a,int& val) -> void
{
    if(r == n + 1)
    {
        val = std::max(val,v);
        return;
    }
    if(dp[r][i] == -1 or v > dp[r][i])
    {
        dp[r][i] = v;
        dfs(r + 1, i, v + a[r][i], n, a, val);
        dfs(r + 1, i + 1, v + a[r][i], n, a, val);
    }
}

fun dfs(int n,const var& a) -> int
{
    var ret = int{};
    dfs(1,0,0,n,a,ret);
    return ret;
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    var n = int{};
    std::cin >> n;
    var a = std::vector<std::vector<int>>(n + 1);
    for(var i = 1; i <= n; ++i)
    {
        std::copy_n(std::istream_iterator<int>{ std::cin },i,std::back_inserter(a[i]));
    }
    var ans = dfs(n,a);
    print("{:d}",ans);

    return 0;
}