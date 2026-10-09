

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
#include<format>
#include<ranges>
#include<bit>
#include<span>

#define fun auto
#define let auto
#define in :

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

using namespace std::ranges::views;

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();

enum { luogu,codeforces,leetcode };
let constexpr check_ = luogu;


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

fun solve() {
    int n;
    std::cin >> n;
    let dfs = [fw = fenwick<int64>{ n + 1 },vis = fenwick<int64>{ n + 1 },cache = std::vector(n + 1,0LL)](this auto& self,int i) {
        if(i == 1) {
            return 1LL;
        }
        if(i == 2) {
            return 2LL;
        }
        if(cache[i]) {
            return cache[i];
        }
        if(vis(1,i / 2) == i / 2) {
            return 1 + fw(1,i / 2);
        }
        let r = iota(1,i / 2 + 1) | transform([&](int k){ return self(k); });
        cache[i] = std::reduce(r.begin(),r.end(),int64{ 1 });
        vis.add(i,1);
        fw.add(i,cache[i]);
        return cache[i];
    };
    std::cout << dfs(n);
}

fun main() -> signed {
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    if constexpr(check_ == codeforces) { // NOLINT
        let t = 0;
        std::cin >> t;
        while(t--) {
            std::invoke(solve);
        }
    } else {
        std::invoke(solve);
    }
    return 0;
}
