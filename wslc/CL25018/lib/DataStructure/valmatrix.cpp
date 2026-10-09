namespace mat
{

    template<typename T>
    struct matrix;

    template<typename T>
    fun constexpr one(int n) -> matrix<T>
{
    matrix<T> ret(n, n, {});
    for(int i: iota(0, n)) {
    ret[i][i] = 1;
}
return ret;
}

template<typename T, std::integral I>
fun constexpr pow(const matrix<T> &v, I k) -> matrix<T>
{
auto a{ one<T>(v.row()) },tv{ v };
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

    matrix(int n, int m) : matrix(n ,m,{})
    {}

    matrix(int n, int m, const T &val) : a(val,n * m),m{ m }
    {}

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
    constexpr matrix(U const (&il)[M_],R const (&...ils)[M_]) : matrix(1 + sizeof...(ils),M_)
    {
        for(let i = 0; i != M_; ++i) {
            a[i] = il[i];
        }
        if constexpr (sizeof...(ils)) {
            make_matrix<1, M_, R...>(ils...);
        }
    }

    fun constexpr operator[](std::size_t i) noexcept
    { return a[std::slice{ i * cow(),std::size_t(cow()),1ull }]; }

    fun constexpr operator[](std::size_t i) const noexcept
    { return a[std::slice{ i * cow(),std::size_t(cow()),1ull}]; }

    fun constexpr operator^(std::integral auto n) -> matrix
    { return mat::pow(*this,n); }

    fun constexpr operator*=(const T &val)
    { std::ranges::transform(a, a + row() * cow(), a, [&val](const T &v) -> T { return v * val; }); }

    fun constexpr operator%=(const T &val)
    { std::ranges::transform(a, a + row() * cow(), a, [&val](const T &v) -> T { return v % val; }); }

    fun constexpr operator>>=(const matrix& v) -> matrix&
    { return *this = v * *this; }

    fun constexpr operator<<=(const matrix& v) -> matrix&
    { return *this = *this * v; }

    fun friend operator>>(std::istream& is,matrix& v) -> std::istream&
    {
        v.a.apply([&](T& val){ is >> val; });
        return is;
    }

    fun friend operator<<(std::ostream& os,const matrix& v) -> std::ostream&
    {
        for(int i : iota(0,v.row())) {
            let s = decltype(a){ v[i] };
            for(let const& val in s) {
                std::cout << val << ' ';
            }
            os << '\n';
        }
        return os;
    }

    [[nodiscard]]
    fun constexpr row() const noexcept -> int
    {
        return a.size() / m;
    }

    [[nodiscard]]
    fun constexpr cow() const noexcept -> int
    {
        return m;
    }

    template<typename U1,typename U2>
    fun friend constexpr operator*(const matrix<U1> &x, const matrix<U2> &y) -> matrix<std::common_type_t<U1, U2>>;

private:
    std::valarray<T> a{};
    int m;
public:

    fun one() -> matrix
    { return one<T>(row()); }

};

template<typename U,typename... R,int M_>
matrix(U const (&il)[M_],R const (&...ils)[M_]) -> matrix<std::common_type_t<U,R...>>;

template<typename U1, typename U2>
requires std::common_with<U1,U2>
fun constexpr operator*(const matrix<U1> &x, const matrix<U2> &y)
-> matrix<std::common_type_t<U1,U2>>
{
using Ret = std::common_type_t<U1,U2>;
matrix<Ret> v(x.row(), y.cow());
for(int i: iota(0, x.row())) {
for(int c: iota(0, x.cow())) {
for(int j: iota(0, y.cow())) {
v[i][j] += x[i][c] * y[c][j];
}
}
}
return v;
}

}

template<typename T>
fun operator<<(std::ostream& os,std::valarray<T> const& val) -> std::ostream&
{ std::ranges::copy(val,std::ostream_iterator<T>{ os," " }); return os; }

using mat::matrix;