

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

constexpr int INF{ 0x3f3f3f3f };



template<typename T = int,typename Ret = T>
requires std::is_integral_v<T> and std::is_integral_v<Ret>
struct xds
{

    explicit xds(int n) noexcept : a(std::vector<T>(n << 2)),lazy_(std::vector<T>(n << 2)){}

    template<std::random_access_iterator It>
    requires requires(It it) { { *it } -> std::convertible_to<T>; }
    xds(It first_,It end_) noexcept
    {
        int n{ static_cast<int>(std::distance(first_,end_)) };
        a.resize(n << 2);
        lazy_.resize(n << 2);
        build(0,n - 1,0,first_);
    }

    [[nodiscard]]
    fun sum(int l,int r) noexcept -> Ret
    {
        return sum(0,(a.size() >> 2) - 1,0,l,r);
    }

    fun add(int l,int r,T v) noexcept -> void
    {
        add(0,(a.size() >> 2) - 1,0,l,r,v);
    }

private:

    fun add(int l,int r,int i,int lt,int rt,T v) -> void
    {
        if(lt <= l and r <= rt) {
            lazy_[i] += v;
            a[i] += (r - l + 1) * v;
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

    fun sum(int l,int r,int i,int lt,int rt) noexcept -> Ret
    {
        if(lt <= l and r <= rt) {
            return a[i];
        }
        int mid{ (l + r) >> 1 };
        update(i,mid - l + 1,r - mid);
        Ret ret{};
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
        if(lazy_[i]) {
            int lt{ left(i) },rt{ right(i) };
            lazy_[lt] += lazy_[i];
            lazy_[rt] += lazy_[i];
            a[lt] += ln * lazy_[i];
            a[rt] += rn * lazy_[i];
            lazy_[i] = 0;
        }
    }

    fun merge(int i) noexcept -> void
    {
        a[i] = a[left(i)] + a[right(i)];
    }

    template<std::random_access_iterator It>
    fun build(int l,int r,int i,It first_) noexcept -> void
    {
        if(l == r) {
            a[i] = first_[l];
        } else {
            int mid{ (l + r) >> 1 };
            update(i,mid - l + 1,r - mid);
            build(l,mid,left(i),first_);
            build(mid + 1,r,right(i),first_);
            merge(i);
        }
    }

    fun static constexpr left(int i) noexcept -> int { return (i << 1) | 1; }
    fun static constexpr right(int i) noexcept -> int { return left(i) + 1; }

    std::vector<T> a;
    std::vector<T> lazy_;
};




template<typename T>
requires std::is_integral_v<T>
fun constexpr lg2(T n) noexcept -> int
{
    int log{};
    if constexpr(sizeof(T) >= 8)
    { if (n >= T{ 1 } << 32) { n >>= 32; log += 32; } }
    if constexpr(sizeof(T) >= 4)
    { if (n >= T{ 1 } << 16) { n >>= 16; log += 16; } }
    if constexpr(sizeof(T) >= 2)
    { if (n >= T{ 1 } << 8) { n >>= 8; log += 8; } }
    if (n >= T{ 1 } << 4) { n >>= 4; log += 4; }
    if (n >= T{ 1 } << 2) { n >>= 2; log += 2; }
    if (n >= T{ 1 } << 1) { log += 1; }
    return log;
}

template<typename T>
requires std::is_integral_v<T>
struct fenwick
{

    explicit fenwick(int n) noexcept : a(std::vector<T>(n)) {}

    fun add(int i,T v) noexcept
    {
        for(; i <= a.size(); i += i & -i)
        {
            a[i - 1] += v;
        }
    }

    fun sum(int i) const noexcept -> T
    {
        T ret{};
        for(; i; i -= i & -i)
        {
            ret += a[i - 1];
        }
        return ret;
    }

    fun sum(int l,int r) const noexcept -> T
    {
        return sum(r) - sum(l - 1);
    }

    fun select(T k) const noexcept -> int = delete;

    std::vector<T> a;
};

fun solve()
{
    int n,m;
    std::cin >> n >> m;
    std::vector<int> a(n);
    for(int i : iota(0,n)) {
        std::cin >> a[i];
    }
    fenwick<int64> fw{ n + 2 };
    fenwick<int64> ifw{ n + 2 };
    for(int i : iota(0,m)) {
        int opt;
        std::cin >> opt;
        if(opt == 1) {
            int l,r,k,d;
            std::cin >> l >> r >> k >> d;
            //--l,--r;
            fw.add(l,k);
            ifw.add(l,1ll * l * k);
            fw.add(l + 1,d - k);
            ifw.add(l + 1,1ll * (l + 1) * (d - k));
            fw.add(r + 1,-k - 1ll * (r - l + 1) * d);
            ifw.add(r + 1,(r + 1) * 1ll * (-k - (r - l + 1) * d));
            fw.add(r + 2,k + 1ll * (r - l) * d);
            ifw.add(r + 2,1ll * (r + 2) * (k + (r - l) * d));

        } else {
            int p;
            std::cin >> p;
            //--p;
            println((p + 1) * fw.sum(p) - ifw.sum(p) + a[p - 1]);
        }
    }
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}
