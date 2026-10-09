

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

template<typename T = int,typename Ret = T>
requires std::is_integral_v<T> and std::is_integral_v<Ret>
struct xds
{

    template<std::random_access_iterator It,typename Se>
    requires requires(It it) { { *it } -> std::convertible_to<T>; } and std::sentinel_for<Se,It>
    xds(It first_,Se end_) noexcept
    {
        int n{ static_cast<int>(std::distance(first_,end_)) };
        a.resize(n << 2);
        lazy_.resize(n << 2);
        lazy2.resize(n << 2,INF);
        build(0,n - 1,0,first_);
    }

    template<std::ranges::range Range>
    explicit xds(Range&& r) noexcept : xds(std::ranges::begin(r),std::ranges::end(r)) {}

    [[nodiscard]]
    fun max(int l,int r) noexcept -> Ret
    {
        return max(0,(a.size() >> 2) - 1,0,l,r);
    }

    fun add(int l,int r,T v) noexcept -> void
    {
        add(0,(a.size() >> 2) - 1,0,l,r,v);
    }

    fun modify(int l,int r,T v) noexcept -> void
    {
        modify(0,(a.size() >> 2) - 1,0,l,r,v);
    }

private:

    fun add(int l,int r,int i,int lt,int rt,T v) -> void
    {
        if(lt <= l and r <= rt) {
            lazy_[i] += v;
            a[i] += v;
        } else {
            int mid{ (l + r) >> 1 };
            update(i,mid - l + 1,r - mid);
            if(lt <= mid) {
                add(l,mid,left(i),lt,rt,v);
            }
            if(rt > mid) {
                add(mid + 1,r,right(i),lt,rt,v);
            }
            merge(i);
        }
    }

    fun modify(int l,int r,int i,int lt,int rt,T v) -> void
    {
        if(lt <= l and r <= rt) {
            lazy_[i] = 0;
            lazy2[i] = v;
            a[i] = v;
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

    fun max(int l,int r,int i,int lt,int rt) noexcept -> Ret
    {
        if(lt <= l and r <= rt) {
            return a[i];
        }
        int mid{ (l + r) >> 1 };
        update(i,mid - l + 1,r - mid);
        Ret ret{ -LNF };
        if(lt <= mid) {
            ret = std::max(ret,max(l,mid,left(i),lt,rt));
        }
        if(rt > mid) {
            ret = std::max(ret,max(mid + 1,r,right(i),lt,rt));
        }
        return ret;
    }

    fun update(int i,int ln,int rn) noexcept -> void
    {
        if(lazy2[i] != INF) {
            int lt{ left(i) },rt{ right(i) };
            lazy2[lt] = lazy2[rt] = lazy2[i];
            lazy_[lt] = lazy_[rt] = 0;
            a[lt] = a[rt] = lazy2[i];
            lazy2[i] = INF;
        }
        if(lazy_[i]) {
            int lt{ left(i) },rt{ right(i) };
            lazy_[lt] += lazy_[i];
            lazy_[rt] += lazy_[i];
            a[lt] += lazy_[i];
            a[rt] += lazy_[i];
            lazy_[i] = 0;
        }
    }

    fun merge(int i) noexcept -> void
    {
        a[i] = std::max(a[left(i)],a[right(i)]);
    }

    template<std::random_access_iterator It>
    fun build(int l,int r,int i,It first_) noexcept -> void
    {
        if(l == r) {
            a[i] = first_[l];
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
    std::vector<T> lazy_;
    std::vector<T> lazy2;
};

fun solve()
{
    int n,q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for(int i : iota(0,n)) {
        std::cin >> a[i];
    }
    xds<int64> fw{ a };
    while(q--) {
        int op;
        std::cin >> op;
        if(op == 1) {
            int l,r,x;
            std::cin >> l >> r >> x;
            --l,--r;
            fw.modify(l,r,x);
        } else if(op == 2) {
            int l,r,x;
            std::cin >> l >> r >> x;
            --l,--r;
            fw.add(l,r,x);
        } else {
            int l,r;
            std::cin >> l >> r;
            --l,--r;
            println(fw.max(l,r));
        }
    }

}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}