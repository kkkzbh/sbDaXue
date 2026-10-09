

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

constexpr int INF{ 1000000000 + 520 };
constexpr int64 LNF { 66666666666666666 };
constexpr int N{ 10000000 + 2 };
constexpr int null{};

int trie[N][2];
int pass[N];
int cnt{};

fun create() -> int
{
    trie[cnt][0] = trie[cnt][1] = 0;
    pass[cnt] = 0;
    return cnt++;
}

fun add(int v)
{
    int it{ 1 };
    for(int k{ 29 }; k >= 0; --k) {
        int& i{ trie[it][v >> k & 1] };
        if(i == null) {
            i = create();
        }
        it = i;
        ++pass[it];
    }
}

fun query(int v) -> int64
{
    int it{ 1 };
    int64 ret{};
    bool tag{};
    for(int k{ 29 }; k >= 0; --k) {
        if(v >> k & 1) {
            if(tag) {
                ret += pass[trie[it][1]];
            } else {
                tag = true;
            }
        }
        it = trie[it][0];
    }
    ret += pass[it];
    return ret;
}

fun solve()
{
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for(int i : iota(0,n)) {
        std::cin >> a[i];
    }
    cnt = 0;
    create();
    create();
    for(int v : a) {
        add(v);
    }
    int64 ans{};
    for(int v : a) {
        ans += query(v);
    }
    println(ans);
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