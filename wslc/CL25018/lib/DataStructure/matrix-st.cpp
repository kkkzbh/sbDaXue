template<typename T>
struct matrix
{
    matrix(int n, int m) : /* a(new T[n * m]) , */ n(n), m(m)
    {}

    matrix(int n, int m, const T &val) : matrix(n, m)
    { std::ranges::fill_n(a, n * m, val); }

    matrix(const matrix &v) : matrix(v.n,v.m)
    { std::ranges::copy_n(v.a, n * m, a); }

    template<typename U>
    requires std::convertible_to<U, T>
    matrix(const matrix<U> &v) : matrix(v.n,v.m)
    { std::ranges::copy_n(v.a, n * m, a); }
/*
    matrix(matrix &&v) noexcept: a(v.a), n(v.n), m(v.m)
    { v.a = nullptr; }
*/
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
/*
    fun operator=(matrix &&v) noexcept -> matrix &
    {
        n = v.n;
        m = v.m;
        a = v.a;
        v.a = nullptr;
        return *this;
    }
*/
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

    fun solve() -> int
    {
        let constexpr eps = 1e-6;
        let dr = 0;
        for(let i in std::views::iota(0, n)) {
            let ir = std::views::iota(i, n);
            let it = *std::ranges::find_if(ir, [](auto v) { return v; }, [&](auto k) { return (*this)[k][i]; });
            while(it == n and i + dr + 2 < m) {
                tapply(i, m - 1 - ++dr, std::ranges::swap);
                it = *std::ranges::find_if(ir, [](auto v) { return v; }, [&](auto k) { return (*this)[k][i]; });
            }
            if(it == n) {
                return -std::ranges::any_of(ir, [](auto v) { return std::abs(v) >= eps; },
                                            [&](auto i) { return (*this)[i][m - 1]; });
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
        return 1;
    }
/*
    ~matrix()
    { delete[] a; }
*/
    template<typename U1, typename U2>
    fun friend operator*(const matrix<U1> &x, const matrix<U2> &y) -> matrix<std::common_type_t<U1, U2>>;

    int n, m;
private:
    T a[20];
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