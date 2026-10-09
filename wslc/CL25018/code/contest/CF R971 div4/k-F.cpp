

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

constexpr int INF = std::numeric_limits<int>::max();
constexpr int64 INF64 = std::numeric_limits<int64>::max();

fun solve()
{
    int n,q;
    std::cin >> n >> q;
    fenwick<int64> fw{ n };
    for(int i : iota(0,n)) {
        int v;
        std::cin >> v;
        fw.add(i,v);
    }
    while(q--) {
        int64 ans{};
        int64 l,r;
        std::cin >> l >> r;
        --l,--r;
        int il = l / n,ir = r / n;
        int midlen = ir - il - 1;
        ans += midlen * fw(n - 1);
        int pl = l % n,pr = r % n;
        if(pl >= n - il) {
            ans += fw(pl - n + il,il - 1);
        } else {
            ans += fw(il + pl,n - 1);
            if(il - 1 >= 0) {
                ans += fw(0, il - 1);
            }
        }
        if(pr >= n - ir) {
            if(pr - n + ir >= 0) {
                ans += fw(0, pr - n + ir);
            }
            ans += fw(ir,n - 1);
        } else {
            ans += fw(ir,ir + pr);
        }
        std::cout << ans << '\n';
    }

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