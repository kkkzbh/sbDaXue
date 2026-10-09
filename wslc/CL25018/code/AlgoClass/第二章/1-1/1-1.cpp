

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

template<typename T = int,typename Ret = T>
struct xds
{
    template<std::integral I>
    explicit xds(I n) noexcept : a(decltype(a)(n << 2)),lazy(decltype(lazy)(n << 2)){}

    template<std::random_access_iterator It,typename Se>
    requires requires(It it) { { *it } -> std::convertible_to<T>; } and std::sentinel_for<Se,It>
    xds(It first_,Se end_) noexcept : xds(std::distance(first_,end_))
    { build(0,std::distance(first_,end_) - 1,0,first_); }

    template<std::ranges::random_access_range Range>
    explicit xds(Range&& r) noexcept : xds(std::ranges::begin(r),std::ranges::end(r)) {}

    [[nodiscard]]
    fun sum(int l,int r) noexcept -> Ret
    {
        return sum(0,(a.size() >> 2) - 1,0,l,r);
    }

    fun add(int l,int r,T v) noexcept -> void
    {
        add(0,(a.size() >> 2) - 1,0,l,r,v);
    }

    [[nodiscard]]
    fun size() const noexcept -> int
    {
        return a.size() >> 2;
    }

private:

    fun add(int l,int r,int i,int lt,int rt,T v) -> void
    {
        if(lt <= l and r <= rt) {
            lazy[i] += v;
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
        if(lazy[i]) {
            int lt{ left(i) },rt{ right(i) };
            lazy[lt] += lazy[i];
            lazy[rt] += lazy[i];
            a[lt] += ln * lazy[i];
            a[rt] += rn * lazy[i];
            lazy[i] = 0;
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
            build(l,mid,left(i),first_);
            build(mid + 1,r,right(i),first_);
            merge(i);
        }
    }

    fun static constexpr left(int i) noexcept -> int { return (i << 1) | 1; }
    fun static constexpr right(int i) noexcept -> int { return left(i) + 1; }

    std::vector<T> a;
    std::vector<T> lazy;
};

fun solve(auto& is,auto& os)
{
    int n;
    is >> n;
    std::vector<int> a;
    for(; n; n /= 10) {
        a.push_back(n % 10);
    }
    let pow = [](int64 num,std::integral auto p) -> int64 {
        if(p < 0) {
            return 0LL;
        }
        int64 ret{ 1 };
        for(; p; num *= num,p >>= 1) {
            if(p & 1) {
                ret *= num;
            }
        }
        return ret;
    };
    xds<int64> fw{ 10 };
    for(int bit{},val{}; int v : a) {
        if(v) {
            fw.add(0,9,v * bit * pow(10,bit - 1));
            fw.add(0, v - 1, pow(10, bit));
        }
        fw.add(v,v,val + 1);
        val += v * pow(10,bit);
        ++bit;
    }
    for(int bit : iota(0,static_cast<int>(a.size())) | reverse) {
        fw.add(0,0,-pow(10,bit));
    }
    for(int i : iota(0,9)) {
        os << fw.sum(i,i) << '\n';
    }
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    for(int i{}; i <= 9; ++i) {
        std::ifstream is{ std::format("../AlgoClass/1-1/test/count{}.in",i) };
        std::ofstream os{ std::format("../AlgoClass/1-1/out/ans{}.out",i) };
        solve(is,os);
    }
}