

#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>

// dp[i] 表示 搜刮前i个城市能得到的最大物资数量
// dp[i] = max { dp[i - 1], dp[i - 2] + a[i] }

#define fun auto

using int64 = long long;
using namespace std::views;

template<typename T,typename Ret = T>
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

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    std::vector<int> a;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,std::back_inserter(a));
    xds<int64> fw{ a.begin(),a.end() };
    for(int i : iota(0,m)) {
        int op,x,y;
        std::cin >> op >> x >> y;
        --x,--y;
        if(op == 1) {
            int k;
            std::cin >> k;
            fw.add( x,y,k);
        } else {
            std::cout << fw.sum(x,y) << '\n';
        }
    }

    return 0;
}