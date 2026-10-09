namespace omat
{

    template<typename T>
    struct matrix;

    template<typename T>
    fun one(int n) -> matrix<T>
{
    matrix<T> ret(n, n, {});
    for(int i: iota(0, n)) {
    ret[i][i] = 1;
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

    matrix(std::initializer_list<std::initializer_list<T>> il) : matrix(il.size(), (il.begin())->size())
    {
        T *it = a;
        for(auto v: il) {
            it = std::ranges::copy(v, it).out;
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

    fun operator*=(const T &val)
    { std::ranges::transform(a, a + n * m, a, [&val](const T &v) -> T { return v * val; }); }

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
        for(int i : iota(0,v.row())) {
            std::ranges::copy_n(it,v.cow(),std::ostream_iterator<T>{ std::cout," " });
            std::cout << '\n';
            it += v.cow();
        }
        return os;
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
fun make(std::initializer_list<std::initializer_list<T>> il) -> matrix<T>
{ return matrix<T>{ il }; }

}