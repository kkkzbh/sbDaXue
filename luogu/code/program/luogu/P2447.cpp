

#include<iostream>
#include<vector>
#include<ranges>
#include<algorithm>
#include<numeric>
#include<format>

#define fun auto
#define let auto
#define in :

using namespace std::views;

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

template<typename T>
struct matrix;

template<typename T>
fun one(int n) -> matrix<T>
{
    matrix<T> ret(n, n, {});
    for(int i: iota(0, n)) {
        ret[i][i] = T{ 1 };
    }
    return ret;
}

template<typename T, std::integral I>
fun pow(const matrix<T> &v, I k) -> matrix<T>
{
    auto a{ one<T>(v.n) },tv{ v };
    for(; k; k >>= 1) {
        if(k & 1) {
            a = a * tv;
        }
        tv = tv * tv;
    }
    return a;
}

template<typename T>
struct matrix
{
    matrix(int n, int m) : a(new T[n * m]), n(n), m(m)
    {}

    matrix(int n, int m, const T &val) : matrix(n, m)
    { std::ranges::fill_n(a, n * m, val); }

    matrix(const matrix &v) : matrix(v.n,v.m)
    { std::ranges::copy_n(v.a, n * m, a); }

    template<typename U>
    requires std::convertible_to<U, T>
    matrix(const matrix<U> &v) : matrix(v.n,v.m)
    { std::ranges::copy_n(v.a, n * m, a); }

    matrix(matrix &&v) noexcept: a(v.a), n(v.n), m(v.m)
    { v.a = nullptr; }

    template<int N_, int M_>
    constexpr matrix(const T (&il)[N_][M_]) : matrix(N_,M_)
    {
        T *it = a;
        for(auto &v: il) {
            std::ranges::copy(v, it);
            it += M_;
        }
    }

    template<int I,int M_,typename U>
    fun constexpr make_matrix(U const (&il)[M_])
    {
        let d = I * M_;
        for(let i = 0; i != M_; ++i) {
            a[d + i] = il[i];
        }
    }

    template<int I,int M_,typename U,typename... R>
    fun constexpr make_matrix(U const (&il)[M_],R const (&...ils)[M_])
    {
        let d = I * M_;
        for(let i = 0; i != M_; ++i) {
            a[d + i] = il[i];
        }
        make_matrix<I + 1,M_,R...>(ils...);
    }

    template<typename U,typename... R,int M_>
    constexpr matrix(U const (&il)[M_],R const (&...ils)[M_]) : matrix(sizeof...(ils) + 1,M_)
    {
        for(let i = 0; i != M_; ++i) {
            a[i] = il[i];
        }
        if constexpr (sizeof...(ils)) {
            make_matrix<1, M_, R...>(ils...);
        }
    }

    template<typename U>
    fun operator=(const matrix<U> &v) -> matrix &
    {
        n = v.n;
        m = v.m;
        T *tmp = new T[n * m];
        std::ranges::copy_n(v.a, n * m, tmp);
        a = tmp;
        return *this;
    }

    fun operator=(matrix &&v) noexcept -> matrix &
    {
        n = v.n;
        m = v.m;
        a = v.a;
        v.a = nullptr;
        return *this;
    }

    fun operator[](int i) noexcept -> T *
    { return a + (i * m); }

    fun operator[](int i) const noexcept -> const T *
    { return a + (i * m); }

    fun operator^(std::integral auto p) -> matrix<T>
    { return pow(*this, p); }

    fun operator*=(const T &val)
    { std::ranges::transform(a, a + n * m, a, [&val](const T &v) -> T { return v * val; }); }

    fun operator*=(matrix const& v)
    { return *this = *this * v; }

    fun operator%=(const T &val)
    { std::ranges::transform(a, a + n * m, a, [&val](const T &v) -> T { return v % val; }); }

    fun operator>>=(const matrix& v) -> matrix&
    { return *this = v * *this; }

    fun operator<<=(const matrix& v) -> matrix&
    { return *this = *this * v; }


    fun friend operator>>(std::istream& is,matrix& v) -> std::istream&
    { std::copy_n(std::istream_iterator<T>{ is },v.n * v.m,v.a); return is; }

    fun friend operator<<(std::ostream& os,const matrix& v) -> std::ostream&
    {
        T* it = v.a;
        for(int i : iota(0,v.n)) {
            std::ranges::copy_n(it,v.m,std::ostream_iterator<T>{ std::cout," " });
            std::cout << '\n';
            it += v.m;
        }
        return os;
    }

    template<std::invocable<T &, T &> Op>
    fun apply(int i, int j, Op op) -> void
    {
        let x = (*this)[i], y = (*this)[j];
        for(let _ in std::views::iota(0, m)) {
            op(*x++, *y++);
        }
    }

    template<std::invocable<T &, T &> Op>
    fun tapply(int i, int j, Op op) -> void
    {
        let x = a + i, y = a + j;
        for(let _ in std::views::iota(0, n)) {
            op(*x, *y);
            x += m, y += m;
        }
    }

    fun solve() -> std::tuple<bool,int,int>
    {

        let constexpr NOTE =
                "返回是否有解,rank,使用方程个数"
                "如果无解，第三个参数无意义"
        ;
        let constexpr eps = 1e-6;
        let dr = 0,cnt = 0;
        for(let i in std::views::iota(0, std::min(n,m - 1))) {
            let ir = std::views::iota(i, n);
            let it = *std::ranges::find_if(ir, [](auto const& v) { return bool(v); }, [&](auto k) { return (*this)[k][i]; });
            while(it == n and i + dr + 2 < m) {
                tapply(i, m - 1 - ++dr, std::ranges::swap);
                it = *std::ranges::find_if(ir, [](auto const& v) { return bool(v); }, [&](auto k) { return (*this)[k][i]; });
            }
            cnt = std::max(cnt,it);
            if(it == n) {
                return { std::ranges::any_of(ir, [](auto const& v) {
                    if constexpr(std::floating_point<T>) {
                        return std::abs(v) >= eps;
                    } else {
                        return bool(v);
                    }
                },[&](auto i) { return (*this)[i][m - 1]; }),i + 1,cnt + 1 };
            }
            if(it != i) {
                apply(it, i, std::ranges::swap);
            }
            if(std::abs((*this)[i][i] - 1) >= eps) {
                for(let j in std::views::iota(i, m) | std::views::reverse) {
                    (*this)[i][j] /= (*this)[i][i];
                }
            }
            for(let k in iota(0, n) | filter([&](auto k) { return k != i; })) {
                let const &coe = (*this)[k][i];
                apply(i, k, [coe](T &lhs, T &rhs) {
                    rhs -= lhs * coe;
                });
            }
        }
        return { true,m - 1,cnt + 1 };
    }

    ~matrix()
    { delete[] a; }

    template<typename U1, typename U2>
    fun friend operator*(const matrix<U1> &x, const matrix<U2> &y) -> matrix<std::common_type_t<U1, U2>>;

    int n, m;
private:
    T *a;
public:

    fun one() -> matrix
    { return one<T>(n); }

};

template<typename U, typename... R, int M_>
matrix(U const (&il)[M_], R const (&...ils)[M_]) -> matrix<std::common_type_t<U, R...>>;

template<typename U1, typename U2>
fun operator*(const matrix<U1> &x, const matrix<U2> &y) -> matrix<std::common_type_t<U1, U2>>
{
    matrix<std::common_type_t<U1, U2>> v(x.n, y.m, {});
    for(int i: iota(0, x.n)) {
        for(int c: iota(0, x.m)) {
            for(int j: iota(0, y.m)) {
                v[i][j] += x[i][c] * y[c][j];
            }
        }
    }
    return v;
}

template<typename T>
requires std::integral<T> or std::same_as<T,__int128>
fun xor_solve(std::vector<std::vector<T>>& a) -> std::tuple<bool,int,int>
{
    let constexpr NOTE =
            "返回 是否有解 rank 使用方程个数"
            "如果无解,后续参数无意义"
    ;

    let const& n = int(a.size());
    let const& m = int(a[0].size());
    if(n < m - 1) {
        return { false,{},{} };
    }
    let cnt = 0;
    for(let j in iota(0,m - 1)) {
        let rv = iota(j,n);
        let it = *std::ranges::find(rv,true,[&](auto i){ return bool(a[i][j]); });
        if(it == n) {
            return { false,{},{} };
        }
        if(it != j) {
            std::ranges::swap(a[it],a[j]);
        }
        cnt = std::ranges::max(cnt,it);
        for(let k in iota(0,n) | filter([&](auto k){ return k != j and bool(a[k][j]); })) {
            for(let i in iota(0,m)) {
                a[k][i] = a[k][i] ^ a[j][i];
            }
        }

    }
    return { true,m - 1,cnt + 1 };

}

#include<string>

using namespace std::literals::string_literals;

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    let q = 1;
    while(q--) {
        [] {
            int n,m;
            std::cin >> n >> m;
            std::swap(n,m);

            let a = std::vector(n,std::vector(m + 1,char{}));

            for(let i in iota(0,n)) {
                let s = ""s;
                bool b;
                std::cin >> s;
                for(let j in iota(0,m)) {
                    a[i][j] = s[j] ^ 48;
                }
                std::cin >> b;
                a[i][m] = b;
            }

            let [flag,rank,cnt] = xor_solve(a);
            if(not flag) {
                std::cout << "Cannot Determine";
                return;
            }

            std::cout << cnt << '\n';

            let constexpr out = std::array {
                    "Earth" "\n",
                    "?y7M#" "\n"
            };

            for(let i in iota(0,m)) {
                std::cout << out[a[i][m]];
            }

        }();
    }


    return 0;
};