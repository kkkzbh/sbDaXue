

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

constexpr int dynamic_mod = -1;

template<int N>
struct type_int;

template<>
struct type_int<32>
{ using type = int; };

template<>
struct type_int<64>
{ using type = int64; };

template<unsigned char bit,std::integral auto MOD = dynamic_mod,std::integral mod_t = decltype(MOD)>
struct mint
{

    using T = typename type_int<bit>::type;

    template<std::integral auto MOD_,std::integral mod_t_>
    struct mod_
    {
        constexpr mod_() = default;
        constexpr mod_(mod_t_ I){}
        constexpr operator mod_t_() const noexcept
        { return MOD_; }
    };

    template<std::integral mod_t_>
    struct mod_<dynamic_mod,mod_t_>
    {
        constexpr mod_() = default;
        constexpr mod_(mod_t_ v) : mod{ v }{}
        constexpr operator mod_t_() const noexcept
        { return mod; }
        mod_t_ mod;
    };

    constexpr mint() = default;
    constexpr mint(T v) requires (MOD != dynamic_mod) : val{ norm(v) }{}
    constexpr mint(T v,mod_t mod) requires (MOD == dynamic_mod) : mod{ mod },val{ norm(v) }{}

    [[nodiscard]]
    fun constexpr norm(T v) const noexcept -> T requires (MOD == dynamic_mod)
    {
        if(v >= mod) {
            v -= mod;
        } else if(v < 0) {
            v += mod;
        }
        return v;
    }

    template<bool big>
    [[nodiscard]]
    fun constexpr norm(T v) const noexcept -> T requires (MOD == dynamic_mod)
    {
        if constexpr(big) {
            if(v >= mod) {
                v -= mod;
            }
        } else {
            if(v < 0) {
                v += mod;
            }
        }
        return v;
    }

    [[nodiscard]]
    fun constexpr static norm(T v) noexcept -> T requires (MOD != dynamic_mod)
    {
        if(v >= MOD) {
            v -= MOD;
        } else if(v < 0) {
            v += MOD;
        }
        return v;
    }

    template<bool big>
    fun constexpr static norm(T v) noexcept -> T requires (MOD != dynamic_mod)
    {
        if constexpr(big) {
            if(v >= MOD) {
                v -= MOD;
            }
        } else {
            if(v < 0) {
                v += MOD;
            }
        }
        return v;
    }

    constexpr operator T() const noexcept
    { return val; }

    fun constexpr operator-() const noexcept
    {
        mint ret;
        ret.val = mod - val;
        return ret;
    }

    fun constexpr operator+=(mint v) -> mint&
    {
        val = norm<true>(val + v.val);
        return *this;
    }

    fun constexpr operator*=(mint v) -> mint&
    {
        val = (static_cast<int64>(val) * v.val) % mod;
        return *this;
    }

    fun constexpr operator-=(mint v) -> mint&
    {
        val = norm<false>(val - v.val);
        return *this;
    }

    fun friend constexpr operator+(mint x,mint y) -> mint
    { return x += y; }

    fun friend constexpr operator*(mint x,mint y) -> mint
    { return x *= y; }

    fun friend constexpr operator-(mint x,mint y) -> mint
    { return x-= y; }

    fun friend operator>>(auto& is,mint& v) -> auto&
    {
        is >> v;
        v = norm(v);
        return is;
    }

    fun friend operator<<(auto& os,mint v) -> auto&
    { return os << v.val; }

    fun friend constexpr operator==(mint x,mint y) -> bool
    { return x.val == y.val; }

    fun friend constexpr operator<=>(mint x,mint y)
    { return x.val <=> y.val; }

    [[no_unique_address]] mod_<MOD,mod_t> mod;
    T val;
};

template<std::integral T,std::integral mod_t>
mint(T v,mod_t t) -> mint<sizeof(T) * 8,dynamic_mod,mod_t>;

template<std::integral auto MOD>
fun constexpr make_mint(std::integral auto I)
{
    return mint<sizeof(I) * 8,MOD>{ I };
}

fun make_mint(std::integral auto I,std::integral auto mod)
{
    return mint{ I,mod };
}



template<typename T = int>
struct fenwick
{
    template<std::integral I>
    explicit fenwick(I n) noexcept : a(std::vector<T>(n)) {}

    [[nodiscard]]
    fun size() const noexcept -> int
    { return a.size(); }

    fun add(int i,T v) noexcept
    {
        for(++i; i <= a.size(); i += i & -i)
        {
            a[i - 1] += v;
        }
    }

    [[nodiscard]]
    fun sum(int i) const noexcept -> T
    {
        T ret{};
        for(++i; i; i -= i & -i)
        {
            ret += a[i - 1];
        }
        return ret;
    }

    [[nodiscard]]
    fun sum(int l,int r) const noexcept -> T
    {
        return sum(r) - sum(l - 1);
    }

    fun operator()(int i) const noexcept -> T
    {
        return sum(i);
    }

    fun operator()(int l,int r) const noexcept -> T
    {
        return sum(l,r);
    }

    fun clear() noexcept
    {
        std::ranges::fill(a,T{});
    }

    [[nodiscard]]
    fun select(T k) const noexcept -> int = delete;

    std::vector<T> a;
};


fun solve()
{
    int n;
    std::cin >> n;
    std::vector v1(n,0),v2(n,0);
    std::copy_n(std::istream_iterator<int>{ std::cin },n,v1.begin());
    std::copy_n(std::istream_iterator<int>{ std::cin },n,v2.begin());
    std::vector ia(n,0),ib(n,0);
    std::iota(ia.begin(),ia.end(),0);
    std::iota(ib.begin(),ib.end(),0);
    std::ranges::sort(ia,std::less<>{},[&](int i){ return v1[i]; });
    std::ranges::sort(ib,std::less<>{},[&](int i){ return v2[i]; });
    std::vector cast(n,0);
    for(int i : iota(0,n)) {
        cast[ia[i]] = ib[i];
    }
    let ans = make_mint<1000'000'00 - 3>(0);
    fenwick fw{ n };
    for(auto val : cast | reverse) {
        ans += fw(val - 1);
        fw.add(val,1);
    }
    std::cout << ans;
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}