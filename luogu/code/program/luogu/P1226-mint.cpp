

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

template<typename Num,std::integral Power>
fun constexpr pow(Num num,Power power) -> Num
{
    Num ret{ 1,num.mod };
    for(; power; power >>= 1,num *= num) {
        if(power & 1) {
            ret *= num;
        }
    }
    return ret;
}

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

fun solve()
{
    int a,b,p;
    std::cin >> a >> b >> p;
    let ma = make_mint(int64{ a },p);
    std::cout << a << '^' << b << " mod " << p << '=' << pow(ma,b);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}