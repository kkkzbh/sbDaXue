

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
#include<optional>

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

template<typename T = int,typename Ret = T>
struct xds
{
    template<std::integral I>
    explicit xds(I n) noexcept : a(std::vector<T>(n << 2)),lazy_(std::vector<T>(n << 2)){}

    template<std::random_access_iterator It,typename Se>
    requires requires(It it) { { *it } -> std::convertible_to<T>; } and std::sentinel_for<Se,It>
    xds(It first_,Se end_) noexcept
    {
        int n{ static_cast<int>(std::distance(first_,end_)) };
        a.resize(n << 2);
        lazy_.resize(n << 2);
        build(0,n - 1,0,first_);
    }

    template<std::ranges::range Range>
    explicit xds(Range&& r) noexcept : xds(std::ranges::begin(r),std::ranges::end(r)) {}

    [[nodiscard]]
    fun sum(int l,int r) noexcept -> Ret
    {
        return sum(0,(a.size() >> 2) - 1,0,l,r);
    }

    fun add(int l,int r) noexcept -> void
    {
        add(0,(a.size() >> 2) - 1,0,l,r);
    }

    [[nodiscard]]
    fun size() const noexcept -> int
    {
        return a.size() >> 2;
    }

private:

    fun add(int l,int r,int i,int lt,int rt) -> void
    {
        if(lazy_[i] == 1) { // cut
            return;
        }
        if(l == r) {
            lazy_[i] = a[i] = std::sqrt(a[i]);
        } else {
            int mid{ (l + r) >> 1 };
            if(lt <= mid) {
                add(l,mid,left(i),lt,rt);
            }
            if(rt > mid) {
                add(mid + 1,r,right(i),lt,rt);
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
        Ret ret{};
        if(lt <= mid) {
            ret += sum(l,mid,left(i),lt,rt);
        }
        if(rt > mid) {
            ret += sum(mid + 1,r,right(i),lt,rt);
        }
        return ret;
    }

    fun merge(int i) noexcept -> void
    {
        lazy_[i] = std::max(lazy_[left(i)],lazy_[right(i)]);
        a[i] = a[left(i)] + a[right(i)];
    }

    template<std::random_access_iterator It>
    fun build(int l,int r,int i,It first_) noexcept -> void
    {
        if(l == r) {
            lazy_[i] = a[i] = first_[l];
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
};

fun solve()
{
    int n;
    std::cin >> n;
    std::vector<int64> a;
    std::copy_n(std::istream_iterator<int64>{ std::cin },n,std::back_inserter(a));
    int m;
    std::cin >> m;
    xds<int64> fw{ a };
    for(int i : iota(0,m)) {
        int k,l,r;
        std::cin >> k >> l >> r;
        --l,--r;
        if(l > r) {
            std::swap(l,r);
        }
        if(k == 0) {
            fw.add(l,r);
        } else {
            println(fw.sum(l,r));
        }
    }
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}