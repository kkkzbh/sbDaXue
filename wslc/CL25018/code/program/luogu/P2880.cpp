

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

#if __cplusplus >= 202002L
#include<format>
#include<ranges>
#include<bit>
#include<span>
#endif

#define fun auto
#define ref decltype(auto)
#define main fun main
#define let auto
#define type(T) decltype(T)
#define cast static_cast
#define make_range(A) std::begin(A),std::end(A)

#if __cplusplus >= 202002L

#define list std::ranges::random_access_range auto
#define range std::ranges::range auto

#else

#define list auto

#endif

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

#if __cplusplus >= 202002L
using namespace std::views;

template<typename T>
concept STD_array = requires(T array)
{
    typename T::value_type;
    { array[0] } -> std::same_as<std::add_lvalue_reference<typename T::value_type>>;
};

template<typename T>
concept Array = STD_array<T> or std::is_array_v<T>;

template<typename... Args>
fun print(const std::format_string<Args...> fmts,Args&&... args)
{
    std::cout << std::vformat(fmts.get(), std::make_format_args(args...));
}

template<typename T>
fun print(T&& arg)
{
    print("{}",arg);
}

fun println()
{
    print('\n');
}

template<typename... Args>
fun println(const std::format_string<Args...> fmts,Args&&... args)
{
    print(fmts,std::forward<Args>(args)...);
    println();
}

template<typename T>
fun println(T&& arg)
{
    println("{}",arg);
}

template<Array T>
fun scan(T& array,int n)
{
    if constexpr(std::is_array_v<T>)
    {
        std::copy_n(std::istream_iterator<std::remove_all_extents_t<T>>{ std::cin },n, std::ranges::begin(array) + 1);
    }
    else
    {
        std::copy_n(std::istream_iterator<typename T::value_type>{ std::cin },n,array.begin() + 1);
    }
}

template<Array T,std::integral... Args>
fun scan(T& array,int n,Args... args)
{
    for(int i : iota(1,n + 1))
    {
        scan(array[i],args...);
    }
}

template<typename... Args>
fun scan(Args&... args)
{
    (std::cin >> ... >> args);
}
#endif

namespace fasti
{
    struct istream
    {
        constexpr static int n{ 640000 };
        static inline char buffer[n], *l{ buffer }, *r{ l };
        static istream cin;
        static inline bool normal{ true };

        operator bool()
        {
            return normal;
        }

        fun static get() -> char
        {
            if(l == r) {
                if(r = (l = buffer) + fread(buffer, 1, n, stdin); l == r) {
                    normal = false;
                    return *l;
                }
            }
            return *l++;
        }

        fun static get(char &c) -> istream&
        {
            c = get();
            return cin;
        }

        fun static peek() -> char
        {
            return *l;
        }

        fun static ignore()
        {
            ++l;
        }

        fun static unget()
        {
            --l;
        }

        fun friend operator>>(istream& is,char& c) -> istream&
        {
            while(normal and isspace(c = get())) {}
            return is;
        }

#if __cplusplus >= 202002L
        template<std::integral T>
#else
        template<typename T>
#endif
        fun friend operator>>(istream& is, T& v) -> istream&
        {
            bool negative{};
            char c{};
            while(get(c) and isspace(c)) {}
            if(!normal) {
                return is;
            }
            if(c == '-') {
                negative = true;
                if(!get(c) or c < '0' or c > '9') {
                    return is;
                }
            }
            v = T{};
            do {
                v = v * 10 + (c ^ 48);
            }while(get(c) and c >= '0' and c <= '9');
            if(negative) {
                v = -v;
            }
            if(normal) {
                unget();
            }
            return is;
        }
    private:
        istream() = default;
    };
}
fasti::istream fasti::istream::cin;
auto& cin =  fasti::istream::cin;

constexpr int INF = 1000000000 + 520;
constexpr int64 LNF = 66666666666666666LL;

template<typename T = int,typename Ret = T>
struct xds
{
    template<std::integral I>
    explicit xds(I n) noexcept : a(decltype(a)(n << 2)),b(type(b)(n << 2)),lazy(decltype(lazy)(n << 2)){}

    template<std::random_access_iterator It,typename Se>
    requires requires(It it) { { *it } -> std::convertible_to<T>; } and std::sentinel_for<Se,It>
    xds(It first_,Se end_) noexcept : xds(std::distance(first_,end_))
    { build(0,std::distance(first_,end_) - 1,0,first_); }

    template<std::ranges::random_access_range Range>
    explicit xds(Range&& r) noexcept : xds(std::ranges::begin(r),std::ranges::end(r)) {}

    [[nodiscard]]
    fun max(int l,int r) noexcept -> Ret
    {
        return max(0,(a.size() >> 2) - 1,0,l,r);
    }

    [[nodiscard]]
    fun min(int l,int r) noexcept -> Ret
    {
        return min(0,(a.size() >> 2) - 1,0,l,r);
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
            lazy[i] = v;
            a[i] = v;
            b[i] = v;
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
        Ret ret{ std::numeric_limits<Ret>::min() };
        if(lt <= mid) {
            ret = std::max(max(l,mid,left(i),lt,rt),ret);
        }
        if(rt > mid) {
            ret = std::max(max(mid + 1,r,right(i),lt,rt),ret);
        }
        return ret;
    }

    fun min(int l,int r,int i,int lt,int rt) noexcept -> Ret
    {
        if(lt <= l and r <= rt) {
            return b[i];
        }
        int mid{ (l + r) >> 1 };
        update(i,mid - l + 1,r - mid);
        Ret ret{ std::numeric_limits<Ret>::max() };
        if(lt <= mid) {
            ret = std::min(min(l,mid,left(i),lt,rt),ret);
        }
        if(rt > mid) {
            ret = std::min(min(mid + 1,r,right(i),lt,rt),ret);
        }
        return ret;
    }

    fun update(int i,int ln,int rn) noexcept -> void
    {
        if(lazy[i]) {
            int lt{ left(i) },rt{ right(i) };
            lazy[lt] = lazy[i];
            lazy[rt] = lazy[i];
            a[lt] = *lazy[i];
            b[lt] = *lazy[i];
            a[rt] = *lazy[i];
            b[rt] = *lazy[i];
            lazy[i] = {};
        }
    }

    fun merge(int i) noexcept -> void
    {
        a[i] = std::max(a[left(i)],a[right(i)]);
        b[i] = std::min(b[left(i)],b[right(i)]);
    }

    template<std::random_access_iterator It>
    fun build(int l,int r,int i,It first_) noexcept -> void
    {
        if(l == r) {
            a[i] = first_[l];
            b[i] = first_[r];
        } else {
            int mid{ (l + r) >> 1 };
            build(l,mid,left(i),first_);
            build(mid + 1,r,right(i),first_);
            merge(i);
        }
    }

    fun static constexpr left(int i) noexcept -> int { return (i << 1) | 1; }
    fun static constexpr right(int i) noexcept -> int { return left(i) + 1; }

    std::vector<T> a,b;
    std::vector<std::optional<T>> lazy;
};

fun solve()
{
    int n,q;
    cin >> n >> q;
    std::vector<int> a(n);
    for(int i : iota(0,n)) {
        cin >> a[i];
    }
    xds fw{ a };
    while(q--) {
        int x,y;
        cin >> x >> y;
        --x,--y;
        println(fw.max(x,y) - fw.min(x,y));
    }

}

main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}