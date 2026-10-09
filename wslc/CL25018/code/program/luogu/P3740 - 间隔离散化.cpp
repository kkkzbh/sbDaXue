

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
#include<unordered_set>

#define fun auto
#define var auto
#define cast static_cast

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
    explicit xds(I n) noexcept : a(decltype(a)(n << 2)),lazy_(decltype(lazy_)(n << 2)){}

    [[nodiscard]]
    fun query(int l,int r) noexcept -> Ret
    {
        return query(0,(a.size() >> 2) - 1,0,l,r);
    }

    fun modify(int l,int r,T v) noexcept -> void
    {
        modify(0,(a.size() >> 2) - 1,0,l,r,v);
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
            a[i] = v;
            lazy_[i] = v;
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

    fun query(int l,int r,int i,int lt,int rt) noexcept -> Ret
    {
        if(lt <= l and r <= rt) {
            return a[i];
        }
        int mid{ (l + r) >> 1 };
        update(i,mid - l + 1,r - mid);
        Ret ret{};
        if(lt <= mid) {
            ret += query(l,mid,left(i),lt,rt);
        }
        if(rt > mid) {
            ret += query(mid + 1,r,right(i),lt,rt);
        }
        return ret;
    }

    fun update(int i,int ln,int rn) noexcept -> void
    {
        if(lazy_[i]) {
            int lt{ left(i) },rt{ right(i) };
            lazy_[lt] = lazy_[rt] = *lazy_[i];
            a[lt] = a[rt] = *lazy_[i];
            lazy_[i] = {};
        }
    }

    fun merge(int i) noexcept -> void
    {
        a[i] = std::max(a[left(i)],a[right(i)]);
    }

    fun static constexpr left(int i) noexcept -> int { return (i << 1) | 1; }
    fun static constexpr right(int i) noexcept -> int { return left(i) + 1; }

    std::vector<T> a;
    std::vector<std::optional<T>> lazy_;
};

struct node
{
    int l,r;
};

fun solve()
{
    int n,m;
    std::cin >> n >> m;
    std::vector<node> a;
    std::vector<int> uq;
    for(int i : iota(0,m)) {
        int l,r;
        std::cin >> l >> r;
        a.emplace_back(l,r);
        uq.push_back(l);
        uq.push_back(r);
        uq.push_back(r + 1);
    }
    std::ranges::sort(uq);
    var ur{ std::ranges::unique(uq) };
    uq.erase(ur.begin(),ur.end());
    xds<int> fw{ uq.size() };
    std::ranges::for_each(a,[&,i = 1](node v) mutable {
        int l = std::ranges::lower_bound(uq,v.l) - uq.begin();
        int r = std::ranges::lower_bound(uq,v.r) - uq.begin();
        fw.modify(l,r,i++);
    });
    std::unordered_set<int> set;
    int ans{};
    for(int i : iota(0,fw.size())) {
        int v{ fw.query(i,i) };
        if(v) {
            if(!set.contains(v)) {
                ++ans;
                set.insert(v);
            }
        }
    }
    println(ans);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}