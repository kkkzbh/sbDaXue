

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

constexpr int INF{ 2000000000 + 520 };
constexpr int64 LNF { 66666666666666666 };

fun solve()
{
    int n,m;
    std::cin >> n >> m;
    if(!m) {
        println("Yes");
        return;
    }
    std::vector<int64> a(n,LNF);
    int p0,x0;
    std::cin >> p0 >> x0;
    if(m == 1) {
        println("Yes");
        return;
    }
    --p0;
    a[p0] = x0;
    int d{ INF };
    for(int i : iota(1,m)) {
        int p,x;
        std::cin >> p >> x;
        --p;
        if((x - x0) % (p - p0) or (d != INF and ((x - x0) / (p - p0)) != d)) {
            println("No");
            for(int j : iota(i + 1,m)) {
                std::cin >> p >> x;
            }
            return;
        }
        if(d == INF) {
            d = (x - x0) / (p - p0);
        }
        a[p] = x;
    }
    for(int i{ p0 - 1 }; i >= 0; --i) {
        if(a[i] == LNF) {
            a[i] = a[i + 1] - d;
        } else if(a[i + 1] - a[i] != d) {
            println("No");
            return;
        }
    }
    for(int i{ p0 + 1 }; i < n; ++i) {
        if(a[i] == LNF) {
            a[i] = a[i - 1] + d;
        } else if(a[i] - a[i - 1] != d) {
            println("No");
            return;
        }
    }
    println("Yes");
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while(t--) {
        std::invoke(solve);
    }
}