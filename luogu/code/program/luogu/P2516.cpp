

#include<bits/extc++.h>

#define fun auto
#define let auto
#define in :

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

using namespace std::ranges::views;

namespace gnu
{
    using namespace __gnu_pbds;
    using namespace __gnu_cxx;
}

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();

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
    constexpr explicit mint(T v) requires (MOD != dynamic_mod) : mod{},val{ norm<false>(v % MOD) }{}
    constexpr mint(T v,mod_t mod) requires (MOD == dynamic_mod) : mod{ mod },val{ norm<false>(v % mod) }{}
    constexpr mint(const mint& v) requires (MOD != dynamic_mod) : mod{},val{ v.val }{}
    constexpr mint(const mint& v) requires (MOD == dynamic_mod) : mod{ v.mod },val{ v.val }{}

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

    [[nodiscard]]
    fun constexpr inv() const -> mint
    {
        return pow(mod - 2);
    }

    [[nodiscard]]
    fun constexpr pow(std::integral auto p) const -> mint requires (MOD == dynamic_mod)
    {
        mint v{ 1,mod },mv{ *this };
        for(; p; p >>= 1) {
            if(p & 1) {
                v *= mv;
            }
            mv *= mv;
        }
        return v;
    }

    [[nodiscard]]
    fun constexpr pow(std::integral auto p) const -> mint requires (MOD != dynamic_mod)
    {
        mint v{ 1 },mv{ *this };
        for(; p; p >>= 1) {
            if(p & 1) {
                v *= mv;
            }
            mv *= mv;
        }
        return v;
    }

    fun constexpr operator^(std::integral auto p) const -> mint
    {
        return pow(p);
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

    fun constexpr operator/=(mint v) -> mint&
    { return *this *= v.inv(); }

    fun friend constexpr operator+(mint x,mint y) -> mint
    {
        x += y;
        return x;
    }

    fun friend constexpr operator*(mint x,mint y) -> mint
    {
        x *= y;
        return x;
    }

    fun friend constexpr operator-(mint x,mint y) -> mint
    {
        x -= y;
        return x;
    }

    fun friend constexpr operator/(mint x,mint y) -> mint
    {
        x /= y;
        return x;
    }

    fun friend operator>>(auto& is,mint& v) -> auto&
    {
        is >> v.val;
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

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);

    let a = std::string{},b = a;
    std::cin >> a >> b;
    a.pop_back();
    b.pop_back();

    let n = int(a.size()),m = int(b.size());
    if(n < m) {
        std::swap(a,b);
        std::swap(n,m);
    }

    let dp = std::vector(2,std::vector(m + 1,0));
    using mi = mint<32,100000000>;
    let cnt = std::vector(2,std::vector(m + 1,mi{ 1 }));

    let scroll = [&] {
        std::swap(dp[0],dp[1]);
        std::swap(cnt[0],cnt[1]);
    };

    for(let i in iota(1,n + 1)) {
        for(let j in iota(1,m + 1)) {
            if(a[i - 1] == b[j - 1]) {
                dp[1][j] = dp[0][j - 1] + 1;
                cnt[1][j] = cnt[0][j - 1];
                if(dp[1][j] == dp[0][j]) {
                    cnt[1][j] += cnt[0][j];
                }
                if(dp[1][j] == dp[1][j - 1]) {
                    cnt[1][j] += cnt[1][j - 1];
                }
            } else {
                dp[1][j] = std::ranges::max(dp[0][j],dp[1][j - 1]);
                if(dp[0][j] == dp[1][j - 1]) {
                    cnt[1][j] = cnt[0][j] + cnt[1][j - 1];
                    if(dp[1][j] == dp[0][j - 1]) {
                        cnt[1][j] -= cnt[0][j - 1];
                    }
                } else if(dp[0][j] < dp[1][j - 1]) {
                    cnt[1][j] = cnt[1][j - 1];
                } else {
                    cnt[1][j] = cnt[0][j];
                }
            }
        }
        scroll();
    }

    std::cout << dp[0][m] << '\n' << cnt[0][m];

    return 0;
}


