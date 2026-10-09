

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

// 修改是怎么修改 1次修改 维护的区间值 = 长度 - 维护的区间值
// lazy是懒住修改值

template<typename T = int,typename Ret = T>
requires std::is_integral_v<T> and std::is_integral_v<Ret>
struct xds
{

    explicit xds(int n) noexcept : a(std::vector<T>(n << 2)),lazy_(std::vector<T>(n << 2)){}

    [[nodiscard]]
    fun sum(int l,int r) noexcept -> Ret
    {
        return sum(0,(a.size() >> 2) - 1,0,l,r);
    }

    fun reverse(int l,int r) noexcept -> void
    {
        reverse(0,(a.size() >> 2) - 1,0,l,r);
    }

    fun reverse(int l,int r,int i,int lt,int rt) -> void
    {
        if(lt <= l and r <= rt) {
            lazy_[i] += 1;  //懒惰机制更新
            a[i] = r - l + 1 - a[i]; // 更改区间值
        } else {
            int mid{ (l + r) >> 1 };
            update(i,mid - l + 1,r - mid); // 懒惰更新
            if(lt <= mid) {
                reverse(l,mid,left(i),lt,rt);
            }
            if(rt > mid) {
                reverse(mid + 1,r,right(i),lt,rt);
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
        if(lazy_[i] & 1) {
            int lt{ left(i) },rt{ right(i) };
            lazy_[lt] += lazy_[i] & 1;
            lazy_[rt] += lazy_[i] & 1;
            a[lt] = ln - a[lt];
            a[rt] = rn - a[rt];
            lazy_[i] = 0;
        }
    }

    fun merge(int i) noexcept -> void
    {
        a[i] = a[left(i)] + a[right(i)];    // merge模块
    }


    fun static constexpr left(int i) noexcept -> int { return (i << 1) | 1; }
    fun static constexpr right(int i) noexcept -> int { return left(i) + 1; }

    std::vector<T> a;
    std::vector<T> lazy_;
};

fun solve()
{
    int n,m;
    std::cin >> n >> m;
    xds fw{ n };
    for(int i : iota(0,m)) {
        int c,a,b;
        std::cin >> c >> a >> b;
        if(c) {
            println(fw.sum(a - 1,b - 1));
        } else {
            fw.reverse(a - 1,b - 1);
        }
    }

}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}