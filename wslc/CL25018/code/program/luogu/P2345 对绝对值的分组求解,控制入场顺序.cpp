

#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<numeric>
#include<cstring>
#include<functional>
#include<string>
#include<bitset>
#include<deque>
#include<queue>
#include<cassert>
#include<stack>
#include<optional>
#include<array>
#include<unordered_set>
#include<unordered_map>
#include<map>
#include<set>
#include<fstream>


#if __cplusplus >= 202002L
#include<format>
#include<ranges>
#include<bit>
#include<span>
#endif

#define fun auto
#define let auto

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

#if __cplusplus >= 202002L
using namespace std::ranges::views;
#endif

constexpr int INF = std::numeric_limits<int>::max();
constexpr int64 INF64 = std::numeric_limits<int64>::max();

template<typename T = int>
struct fenwick
{
    template<std::integral I>
    explicit fenwick(I n) noexcept : a(std::vector<T>(n)) {}

    [[nodiscard]]
    fun size() const noexcept -> int
    { return a.size(); }

    fun add(int i,T v) noexcept
    {
        for(++i; i <= a.size(); i += i & -i)
        {
            a[i - 1] += v;
        }
    }

    [[nodiscard]]
    fun sum(int i) const noexcept -> T
    {
        T ret{};
        for(++i; i; i -= i & -i)
        {
            ret += a[i - 1];
        }
        return ret;
    }

    [[nodiscard]]
    fun sum(int l,int r) const noexcept -> T
    {
        return sum(r) - sum(l - 1);
    }

    fun operator()(int i) const noexcept -> T
    {
        return sum(i);
    }

    fun operator()(int l,int r) const noexcept -> T
    {
        return sum(l,r);
    }

    fun clear() noexcept
    {
        std::ranges::fill(a,T{});
    }

    [[nodiscard]]
    fun select(T k) const noexcept -> int = delete;

    std::vector<T> a;
};

struct node
{
    int v,x;
};

fun solve()
{
    int n;
    std::cin >> n;
    let a = std::vector(n,node{});
    for(auto& [v,x] : a) {
        std::cin >> v >> x;
        --x;
    }
    constexpr int N = 20000;
    fenwick f1{ N },f2{ N };
    std::ranges::sort(a,{},[](node v){ return v.v; });
    int64 ans{};
    for(auto [v,x] : a) {
        int cnt = f1(x);
        int sum = f2(x);
        ans += 1LL * v * ((1LL * cnt * x) - sum);
        int rcnt = f1(x,N - 1);
        int rsum = f2(x,N - 1);
        ans += 1LL * v * (rsum - (1LL * rcnt * x));
        f1.add(x,1);
        f2.add(x,x);
    }
    std::cout << ans;
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}