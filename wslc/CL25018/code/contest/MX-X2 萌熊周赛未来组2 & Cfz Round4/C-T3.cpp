

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>
#include<cmath>
#include<numeric>
#include<cstring>
#include<functional>
#include<string>
#include<bitset>
#include<unordered_map>
#include<deque>
#include<queue>

#define fun auto

using int64 = long long;
using uint64 = unsigned long long;
using namespace std::views;

template<typename... Args>
fun print(const std::format_string<Args...> fmts,Args&&... args)
{
    std::cout << std::vformat(fmts.get(), std::make_format_args(args...));
}

fun println()
{
    std::cout << '\n';
}

template<typename... Args>
fun println(const std::format_string<Args...> fmts,Args&&... args)
{
    std::cout << std::vformat(fmts.get(), std::make_format_args(args...)) << '\n';
}

template<typename T>
fun println(T&& arg)
{
    println("{}",arg);
}

constexpr int INF{ 1000000000 + 520 };
constexpr int64 LNF { 66666666666666666 };

struct node
{
    int i;
    int p;
    int v;
    int l;
};

fun solve()
{
    int n,r;
    std::cin >> n >> r;
    std::vector<int> a(n);
    for(int i : iota(0,n)) {
        std::cin >> a[i];
    }
    std::vector<int> dp(n);
    std::vector<std::vector<node>> d(n);
    if(a[0] != 1) {
        dp[0] = 1;
        d[0].emplace_back(1,0,0,-1);
    }
    dp[1] = dp[0];
    if(!a[1]) {
        dp[1] += 1;
        d[1].emplace_back(1,1,0,a[0]);
    }
    for(int i : iota(2,n)) {
        int imax{ 1 };
        for(auto [index,p,v,l] : d[i - 1]) {
            if(l == a[i]) {
                imax = std::max(imax,index);
                d[i].emplace_back(index,i,a[i],v);
                a[i] ^= 1;
            }
        }
        if(!a[i]) {
            d[i].emplace_back(imax + 1,i,0,1);
        }
        dp[i] = dp[i - 1] + d[i].size();
    }
    if(dp[n - 1] > r) {
        println(-1);
        return;
    }
    println(dp[n - 1]);
    std::vector<node> path;
    for(const auto& v : d) {
        for(const auto& val : v) {
            path.push_back(val);
        }
    }
    std::ranges::stable_sort(path,[](const node& x,const node& y) {
        if(x.i == y.i) {
            return x.p > y.p;
        } else {
            return x.i < y.i;
        }
    });
    for(const auto& val : path) {
        print("{} ",val.p + 1);
    }
    println();
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}