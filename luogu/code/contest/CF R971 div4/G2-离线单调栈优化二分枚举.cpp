

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

#if __cplusplus>= 202302L
#endif

#define fun auto
#define let auto

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

#if __cplusplus >= 202002L
using namespace std::ranges::views;
#endif

template<typename T>
struct xds
{
    template<std::integral I>
    explicit xds(I n) noexcept : a(n << 2,{}),lazy(n << 2){}

    template<std::random_access_iterator It,typename Se>
    requires requires(It it) { { *it } -> std::convertible_to<T>; } and std::sentinel_for<Se,It>
    xds(It first_,Se end_) noexcept : xds(std::distance(first_,end_))
    { build(0,std::distance(first_,end_) - 1,0,first_); }

    template<std::ranges::random_access_range Range>
    explicit xds(Range&& r) noexcept : xds(std::ranges::begin(r),std::ranges::end(r)) {}

    [[nodiscard]]
    fun sum(int l,int r) noexcept -> T
    {
        return sum(0,size() - 1,0,l,r);
    }

    fun modify(int l,int r,T v) noexcept -> void
    {
        modify(0,size() - 1,0,l,r,v);
    }

    [[nodiscard]]
    fun size() const noexcept -> int
    {
        return a.size() >> 2;
    }

private:

    fun modify(int l,int r,int i,int lt,int rt,T v) -> void
    {
        if(lt <= l and r <= rt) {
            lazy[i] = v;
            a[i] = (r - l + 1) * v;
        } else {
            int mid{ (l + r) >> 1 };
            update(i,mid - l + 1,r - mid);
            if(lt <= mid) {
                modify(l,mid,left(i),lt,rt,v);
            }
            if(rt > mid) {
                modify(mid + 1,r,right(i),lt,rt,v);
            }
            merge(i);
        }
    }

    fun sum(int l,int r,int i,int lt,int rt) noexcept -> T
    {
        if(lt <= l and r <= rt) {
            return a[i];
        }
        int mid{ (l + r) >> 1 };
        update(i,mid - l + 1,r - mid);
        T ret{};
        if(lt <= mid) {
            ret += sum(l,mid,left(i),lt,rt);
        }
        if(rt > mid) {
            ret += sum(mid + 1,r,right(i),lt,rt);
        }
        return ret;
    }

    fun update(int i,int ln,int rn) noexcept -> void
    {
        if(lazy[i]) {
            int lt{ left(i) },rt{ right(i) };
            lazy[lt] = lazy[i];
            lazy[rt] = lazy[i];
            a[lt] = ln * *lazy[i];
            a[rt] = rn * *lazy[i];
            lazy[i] = {};
        }
    }

    fun merge(int i) noexcept -> void
    {
        a[i] = std::plus{}(a[left(i)],a[right(i)]);
    }

    template<std::random_access_iterator It>
    fun build(int l,int r,int i,It first_) noexcept -> void
    {
        if(l == r) {
            a[i] = first_[r];
        } else {
            int mid{ (l + r) >> 1 };
            build(l,mid,left(i),first_);
            build(mid + 1,r,right(i),first_);
            merge(i);
        }
    }

    fun static constexpr left(int i) noexcept -> int { return (i << 1) | 1; }
    fun static constexpr right(int i) noexcept -> int { return left(i) + 1; }

    std::vector<T> a;
    std::vector<std::optional<T>> lazy;
};

template<std::random_access_iterator It,typename Se>
xds(It first_,Se end_) -> xds<typename std::iterator_traits<It>::value_type>;

template<std::ranges::random_access_range Range>
xds(Range&& r) -> xds<std::ranges::range_value_t<Range>>;

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();

struct node
{
    int l,r;
    int i;
};

fun solve()
{
    int n,k,q;
    std::cin >> n >> k >> q;
    let a = std::vector(n,0);

    for(int i : iota(0,n)) {
        std::cin >> a[i];
        a[i] -= i;
    }

    let set = std::multiset<int>{};
    let map = std::map<int,int>{};

    for(int i : iota(0,n)) {
        set.insert(0);
    }
    for(int i : iota(0,k - 1)) {
        set.erase(set.find(map[a[i]]));
        ++map[a[i]];
        set.insert(map[a[i]]);
    }

    int nn = n - k + 1;
    let ans = std::vector(nn,0);

    for(int i : iota(k - 1,n)) {
        set.erase(set.find(map[a[i]]));
        ++map[a[i]];
        set.insert(map[a[i]]);

        int it = i - k + 1;
        ans[it] = k - *set.rbegin();

        set.erase(set.find(map[a[it]]));
        --map[a[it]];
        set.insert(map[a[it]]);

    }

    let query = std::vector(q,node{});
    for(int index{}; auto& [l,r,i] : query) {
        std::cin >> l >> r;
        --l,--r;
        i = index++;
    }

    std::ranges::sort(query,std::greater<>{},[](node v){ return v.l; });

    xds<int64> fw{ repeat(INF64,nn) };
    let out = std::vector(q,0LL);
    let stk = std::stack<int>{};
    for(int pivot{ nn }; auto [l,r,i] : query) {
        if(pivot != l) {
            for(int p : iota(l,pivot) | reverse) {
                while(!stk.empty() and ans[p] <= ans[stk.top()]) {
                    stk.pop();
                }
                int next = stk.empty() ? nn : stk.top();
                fw.modify(p,next - 1, ans[p]);
                stk.push(p);
            }
            pivot = l;
        }
        out[i] = fw.sum(l,r - k + 1);
    }
    std::ranges::copy(out,std::ostream_iterator<decltype(out)::value_type>{ std::cout,"\n" });

}

fun main() -> signed
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while(t--) {
        std::invoke(solve);
    }
}