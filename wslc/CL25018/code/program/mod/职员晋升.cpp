

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

let constexpr RI = std::array {
        0.,0.,0.,0.58,0.90,1.12,1.24,1.32,1.41,1.45,1.49
};

fun HEfun(auto& A)
{
    using f = long double;
    let vectorize = [](auto& vec,int j = 0)
    { return iota(0,vec.n) | transform([&,j](auto i) -> auto& { return vec[i][j]; }); };
    let normalization = [&](auto& vec,int j = 0){
        let sum = std::ranges::fold_left(vectorize(vec,j),0.L,std::plus{});
        std::ranges::for_each(vectorize(vec,j),[&](auto& val){ val /= sum; });
    };
    let AA = A;
    std::ranges::for_each(iota(0,AA.m),[&](auto j){ normalization(AA,j); });
    let w = matrix(A.n,1,0.L);
    for(let i in iota(0,A.n)) {
        w[i][0] = std::ranges::fold_left(iota(0,AA.m) | transform([&](auto j){ return AA[i][j]; }),0.L,std::plus{});
    }
    normalization(w);
    let Aw = A * w;
    let lam = std::ranges::fold_left(zip(vectorize(Aw),vectorize(w)) | transform([&](auto const& tp) {
        let const& [d1,d2] = tp;
        return d1 / d2;
    }),0.L,std::plus{}) / A.n;
    std::println("lambda = {:f}",lam);
    std::cout << "w = [ " << w <<  " ]\n";
    return std::make_tuple(lam,w);
}

template<int N = 0>
fun TRfun(auto& A)
{
    let [lam,w] = HEfun(A);
    let CI = (lam - A.n) / (A.n - 1);
    let CR = CI / RI[A.n];
    if constexpr (not N) {
        std::println("CI = {},CR = {}", CI, CR);
    } else if constexpr (N == 1) {
        std::println("CI = {}", CI);
    }
    return std::tuple(lam,w,CI,CR);
}

fun main() -> int
{
    let A21 = matrix {
            { 1.,1. / 2,1. / 3,1. / 2 },
            { 2.,1.,1. / 2,1. },
            { 3.,2.,1.,2. },
            { 2.,1.,1. / 2,1. }
    };

    let B1 = matrix {
            { 1.,1. / 2,1. / 4 },
            { 2.,1.,1. / 3 },
            { 4.,3.,1. },
    };
    let B2 = matrix {
            { 1.,2.,3. },
            { 1. / 2,1.,2. },
            { 1. / 3,1. / 2,1. },
    };
    let B3 = matrix {
            { 1.,1.,2. },
            { 1.,1.,2. },
            { 1. / 2,1. / 2,1. },
    };
    let B4 = matrix {
            { 1.,3.,4. },
            { 1. / 2,1.,2. },
            { 1. / 4,1. / 2,1. },
    };
    std::println("第二层数据如下");
    let [lam,w,CI,CR] = TRfun(A21);
    std::println("第三层");
    std::println("w(1)");
    let [lam31,w31,CI31,CR31] = TRfun<1>(B1);
    std::println("w(2)");
    let [lam32,w32,CI32,CR32] = TRfun<1>(B2);
    std::println("w(3)");
    let [lam33,w33,CI33,CR33] = TRfun<1>(B3);
    std::println("w(4)");
    let [lam34,w34,CI34,CR34] = TRfun<1>(B4);
    std::println();
    let W = matrix(w31.n,4,0.);
    for(let i in iota(0,W.n)) {
        W[i][0] = w31[i][0]; // NOLINT
        W[i][1] = w32[i][0]; // NOLINT
        W[i][2] = w33[i][0]; // NOLINT
        W[i][3] = w34[i][0]; // NOLINT
    }
    let w3 = W * w;
    std::println("第三层对第一层的组合权向量为");
    std::cout << w3 << '\n';
    std::println("第二层与第三层的组合一致性比率为 {}",std::ranges::max({ CI,CI31,CI32,CI33,CI34 }));
    let [_1,_2,_3,CRR] = TRfun(w3);
    std::println("第三层与第一层的组合一致性比率为 {}",CRR);

    return 0;
}
