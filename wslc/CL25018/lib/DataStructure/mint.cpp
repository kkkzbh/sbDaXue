constexpr int dynamic_mod = 0;

struct unified {};
struct sole {};

template<typename T>
concept integer = std::integral<T> or std::same_as<T,__int128>;

template<integer T,integer auto MOD = dynamic_mod,typename tag = unified>
struct mint
{

    using mod_t = T;

    constexpr mint() = default;

    constexpr mint(T v) // NOLINT
            : val{ norm<false>(v % mod) } {}

    [[nodiscard]]
    fun static constexpr norm(T v) noexcept -> T
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
    fun static constexpr norm(T v) noexcept -> T
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
    fun constexpr inv() const -> mint
    {
        return pow(mod - 2);
    }

    [[nodiscard]]
    fun constexpr pow(integer auto p) const -> mint
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

    fun constexpr operator^(integer auto p) const -> mint
    { return pow(p); }

    constexpr explicit operator T() const noexcept
    { return val; }

    constexpr explicit operator bool() const noexcept
    { return bool(val); }

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
        val = (static_cast<long long>(val) * v.val) % mod;
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
        v.val = norm(v.val);
        return is;
    }

    fun friend operator<<(auto& os,mint v) -> auto&
    { return os << v.val; }

    fun friend constexpr operator==(mint x,mint y) -> bool
    { return x.val == y.val; }

    fun friend constexpr operator<=>(mint x,mint y)
    { return x.val <=> y.val; }

    constexpr static mod_t mod = MOD;
    T val;

};

template<integer T>
struct mint<T,dynamic_mod,unified>
{
    using mod_t = T;

    constexpr mint() = default;

    constexpr mint(T v) // NOLINT
            : val{ norm<false>(v % mod) } {}

    [[nodiscard]]
    fun static constexpr norm(T v) noexcept -> T
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
    fun static constexpr norm(T v) noexcept -> T
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
    fun constexpr inv() const -> mint
    {
        return pow(mod - 2);
    }

    [[nodiscard]]
    fun constexpr pow(integer auto p) const -> mint
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

    fun constexpr operator^(integer auto p) const -> mint
    { return pow(p); }

    constexpr explicit operator T() const noexcept
    { return val; }

    constexpr explicit operator bool() const noexcept
    { return *this; }

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
        val = (static_cast<long long>(val) * v.val) % mod;
        return *this;
    }

    fun constexpr operator-=(mint v) -> mint&
    {
        val = norm<false>(val - v.val);
        return *this;
    }

    fun constexpr operator/=(mint v) -> mint&
    { return *this *= v.inv(); }

    fun constexpr operator%=(integer auto I) -> mint&
    {
        val %= I;
        return *this;
    }

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

    fun friend constexpr operator%(mint x,integer auto I) -> mint
    {
        x %= I;
        return x;
    }

    fun friend constexpr operator%(integer auto I,mint x)
    { return I % x.val; }

    fun friend operator>>(auto& is,mint& v) -> auto&
    {
        is >> v.val;
        v.val = norm(v.val);
        return is;
    }

    fun friend operator<<(auto& os,mint v) -> auto&
    {
        if constexpr(std::same_as<T,__int128>) {
            return os << std::format("{}",v.val);
        } else {
            return os << v.val;
        }
    }

    fun friend constexpr operator==(mint x,mint y) -> bool
    { return x.val == y.val; }

    fun friend constexpr operator<=>(mint x,mint y)
    { return x.val <=> y.val; }

    static inline mod_t mod;
    T val;

    fun static set(integer auto I) -> void
    { mod = I; }
};

template<integer T>
struct mint<T,dynamic_mod,sole>
{

};

namespace std
{
    template<integer T>
    fun abs(mint<T,dynamic_mod,unified> const& v)
    { return v; }    // NOLINT

    template<integer T,int N>
    fun abs(mint<T,N,unified> const& v)
    { return v; }      // NOLINT

}