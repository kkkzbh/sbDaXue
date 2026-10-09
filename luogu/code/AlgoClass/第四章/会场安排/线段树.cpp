

#include<iostream>
#include<vector>
#include<algorithm>
#include<ranges>
#include<array>
#include<print>

#define fun auto
#define let auto
#define in :

template<typename T>
struct segment
{
    template<std::integral I>
    explicit segment(I n) noexcept : a(decltype(a)(n << 2)),lazy(decltype(lazy)(n << 2)){}

    template<std::random_access_iterator It,typename Se>
    requires requires(It it) { { *it } -> std::convertible_to<T>; } and std::sentinel_for<Se,It>
    segment(It first_,Se end_) noexcept : segment(std::distance(first_,end_))
    { build(0,std::distance(first_,end_) - 1,0,first_); }

    template<std::ranges::random_access_range Range>
    explicit segment(Range&& r) noexcept : segment(std::ranges::begin(r),std::ranges::end(r)) {}

    [[nodiscard]]
    fun sum(int l,int r) noexcept -> T
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

template<std::random_access_iterator It,typename Se>
segment(It first_,Se end_) -> segment<typename std::iterator_traits<It>::value_type>;

template<std::ranges::random_access_range Range>
segment(Range&& r) -> segment<std::ranges::range_value_t<Range>>;

using namespace std::views;
using node = std::array<int,2>;

fun main() -> int
{
    int k;
    std::cin >> k;
    let a = std::vector(k,node{});
    using dis_t = int;
    let dis = std::vector<dis_t>{};
    for(let &[s,e] in a) {
        std::cin >> s >> e;
        dis.push_back(s),dis.push_back(e);
    }

    std::ranges::sort(dis);
    { let r = std::ranges::unique(dis);
        dis.erase(r.begin(),r.end()); }

    let v = [&](dis_t val) {
        return int(std::distance(dis.begin(),std::ranges::lower_bound(dis,val)));
    };

    let n = int(dis.size());

    let max = n;
    let seg = segment<int>{ n };
    for(let const& [s,e] in a) {
        seg.add(v(s),v(e),1);
    }
    let ans = 0;
    for(let i in iota(0,n)) {
        ans = std::max(ans,seg.sum(i,i));
    }
    std::print("{}",ans);

}