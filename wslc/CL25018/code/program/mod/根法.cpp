

#include<iostream>
#include<vector>
#include<random>
#include<algorithm>
#include<ranges>
#include<print>

#define fun auto
#define let auto
#define in :

using namespace std::views;

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

    template<typename U>
    friend struct matrix;

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

using f = long double;

template<typename T>
fun RTfun(matrix<T>& A)
{
    let vectorize = [](auto&& vec,int j = 0)
    { return iota(0,vec.n) | transform([&,j](auto i) -> auto&& { return vec[i][j]; }); };
    let normalization = [&](auto&& vec,int j = 0){
        let sum = std::ranges::fold_left(vectorize(vec,j),0.L,std::plus{});
        std::ranges::for_each(vectorize(vec,j),[&](auto&& val){ val /= sum; });
    };

    let AA = A;
    std::ranges::for_each(iota(0,AA.m),[&](auto j){ normalization(AA,j); });
    let w = matrix {{
                            { std::ranges::fold_left(iota(0,AA.m) | transform([&](auto i){ return AA[0][i]; }),1.L,std::multiplies{}) },
                            { std::ranges::fold_left(iota(0,AA.m) | transform([&](auto i){ return AA[1][i]; }),1.L,std::multiplies{}) },
                            { std::ranges::fold_left(iota(0,AA.m) | transform([&](auto i){ return AA[2][i]; }),1.L,std::multiplies{}) },
                    }};
    std::ranges::for_each(vectorize(w),[n = A.n](auto&& val){ val = std::pow(val,1.L / n); });
    normalization(w);
    let Aw = A * w;
    let lam = std::ranges::fold_left(zip(vectorize(Aw),vectorize(w)) | transform([&](auto const& tp) {
        let const& [d1,d2] = tp;
        return d1 / d2;
    }),0.L,std::plus{}) / A.n;
    std::println("lambda = {:f}"  "\n"  "特征向量 = [{:f} {:f} {:f}]",
                 lam,w[0][0],w[1][0],w[2][0]
    );
}

fun main() -> int
{
    let A = matrix {
            { f(1),f(2),f(6) },
            { f(1.L / 2),f(1),f(4) },
            { f(1.L / 6),f(1.L / 4),f(1) },
    };
    RTfun(A);

    return 0;
}