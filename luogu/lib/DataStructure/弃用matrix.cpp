namespace mat
{

    template<typename T,int N,int M>
    struct matrix;

    constexpr int dynamic_size = -1;

    template<int N,int M>
    struct size
    {
        constexpr size() = default;
        constexpr size(int,int){}
        constexpr static inline int n{ N },m{ M };
    };

    template<>
    struct size<dynamic_size,dynamic_size>
    {
        size(int n,int m) : n(n),m(m){}
        int n,m;
    };

    template<int N,int M>
    concept dynamic = N == dynamic_size and M == dynamic_size;

    template<typename T,int N = dynamic_size>
    fun constexpr one(int n) -> matrix<T,N,N>
{
    matrix<T,N,N> ret(n, n, {});
    for(int i: iota(0, n)) {
    ret[i][i] = 1;
}
return ret;
}

template<typename T, std::integral I,int N = dynamic_size>
fun constexpr pow(const matrix<T,N,N> &v, I k) -> matrix<T,N,N>
{
auto a{ one<T,N>(v.row()) },tv{ v };
for(; k; k >>= 1) {
if(k & 1) {
a = a * tv;
}
tv = tv * tv;
}
return a;
}

template<typename T,int N = dynamic_size,int M = dynamic_size>
struct matrix
{

    matrix(int n, int m) requires dynamic<N,M> : a(new T[n * m]{}), sz(n,m)
    {}

    constexpr matrix() requires (!dynamic<N,M>) = default;

    matrix(int n, int m, const T &val) requires dynamic<N,M> : matrix(n, m)
    { std::ranges::fill_n(a, n * m, val); }

    explicit constexpr matrix(const T& val) requires (!dynamic<N,M>)
    {
        // std::ranges::fill_n(a,N * M,val);
        for(let i = 0,cei = row() * cow(); i != cei; ++i) {
            a[i] = val;
        }
    }

    constexpr matrix(const matrix &v) : matrix(v.row(),v.cow())
    {
        //std::ranges::copy_n(v.a, v.row() * v.cow(), a);
        for(int i{},cei{ row() * cow() }; i != cei; ++i) {
            a[i] = v.a[i];
        }
    }

    template<typename U>
    requires std::convertible_to<U, T>
    constexpr matrix(const matrix<U,N,M> &v) : matrix(v.row(),v.cow())
    {
        // std::ranges::copy_n(v.a, v.row() * v.cow(), a);
        for(let i = 0,cei = v.row() * v.cow(); i != cei; ++i) {
            a[i] = v[i];
        }
    }

    matrix(matrix &&v) noexcept requires dynamic<N,M> : a(v.a), sz(v.sz)
    { v.a = nullptr; }

    template<int N_,int M_>
    consteval matrix(const T (&il)[N_][M_]) : sz(N_,M_)
    {
        T* it = a;
        for(auto& v : il) {
            std::ranges::copy(v,it);
            it += M;
        }
    }

    template<int I,int M_,typename U>
    fun consteval make_matrix(U const (&il)[M_])
    {
        let d = I * M_;
        for(let i = 0; i != M_; ++i) {
            a[d + i] = il[i];
        }
    }

    template<int I,int M_,typename U,typename... R>
    fun consteval make_matrix(U const (&il)[M_],R const (&...ils)[M_])
    {
        let d = I * M_;
        for(let i = 0; i != M_; ++i) {
            a[d + i] = il[i];
        }
        make_matrix<I + 1,M_,R...>(ils...);
    }

    template<typename U,typename... R,int M_>
    consteval matrix(U const (&il)[M_],R const (&...ils)[M_]) : sz(sizeof...(ils) + 1,M_)
    {
        for(let i = 0; i != M_; ++i) {
            a[i] = il[i];
        }
        if constexpr (sizeof...(ils)) {
            make_matrix<1, M_, R...>(ils...);
        }
    }

    fun constexpr operator=(const matrix& v) -> matrix&
    {
        this->operator=<T,N,M>(v);
        return *this;
    }

    template<typename U,int N_,int M_>
    requires std::convertible_to<U,T>
    fun constexpr operator=(const matrix<U,N_,M_> &v) -> matrix& requires (dynamic<N,M> or (N == N_ and M == M_))
    {
        if constexpr(dynamic<N,M>) {
            sz = { v.row(),v.cow() };
            T *tmp = new T[row() * cow()];
            std::ranges::copy_n(v.a, row() * cow(), tmp);
            delete[] a;
            a = tmp;
        } else {
            std::ranges::copy(v.a,a);
        }
        return *this;
    }

    fun operator=(matrix &&v) noexcept -> matrix& requires dynamic<N,M>
    {
        sz = v.sz;
        std::swap(a,v.a);
        return *this;
    }

    fun constexpr operator[](int i) noexcept -> T*
    { return a + (i * cow()); }

    fun constexpr operator[](int i) const noexcept -> const T*
    { return a + (i * cow()); }

    fun constexpr operator^(std::integral auto n) -> matrix<T,N,M>
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
    { std::copy_n(std::istream_iterator<T>{ is },v.row() * v.cow(),v.a); return is; }

    fun friend operator<<(std::ostream& os,const matrix& v) -> std::ostream&
    {
        T const* it = v.a;
        for(int i : iota(0,v.row())) {
            std::ranges::copy_n(it,v.cow(),std::ostream_iterator<T>{ std::cout," " });
            std::cout << '\n';
            it += v.cow();
        }
        return os;
    }

    [[nodiscard]]
    fun constexpr row() const noexcept
    {
        return sz.n;
    }

    [[nodiscard]]
    fun constexpr cow() const noexcept
    {
        return sz.m;
    }

    template<std::invocable<T&,T&> Op>
    fun apply(int i,int j,Op op) -> void
    {
        let x = (*this)[i],y = (*this)[j];
        for(let _ in std::views::iota(0,cow())) {
            op(*x++,*y++);
        }
    }

    template<std::invocable<T&,T&> Op>
    fun tapply(int i,int j,Op op) -> void
    {
        let x = a + i,y = a + j;
        for(let _ in std::views::iota(0,row())) {
            op(*x,*y);
            x += cow(),y += cow();
        }
    }

    fun solve() -> int
    {
        let constexpr eps = 1e-6;
        let dr = 0;
        for(let i in std::views::iota(0,row())) {
            let ir = std::views::iota(i,row());
            let it = *std::ranges::find_if(ir,[](auto v){ return v; },[&](auto k){ return (*this)[k][i]; });
            while(it == row() and i + dr + 2 < cow()) {
                tapply(i,cow() - 1 - ++dr,std::ranges::swap);
                it = *std::ranges::find_if(ir,[](auto v){ return v; },[&](auto k){ return (*this)[k][i]; });
            }
            if(it == row()) {
                return -std::ranges::any_of(ir, [](auto v) { return std::abs(v) >= eps; },[&](auto i) { return (*this)[i][cow() - 1]; });
            }
            if(it != i) {
                apply(it,i,std::ranges::swap);
            }
            if(std::abs((*this)[i][i] - 1) >= eps) {
                for(let j in std::views::iota(i, cow()) | std::views::reverse) {
                    (*this)[i][j] /= (*this)[i][i];
                }
            }
            for(let k in iota(0,row()) | filter([&](auto k){ return k != i; })) {
                let const& coe = (*this)[k][i];
                apply(i,k,[coe](T& lhs,T& rhs) {
                    rhs -= lhs * coe;
                });
            }
        }
        return 1;
    }

    constexpr ~matrix()
    { if constexpr(dynamic<N,M>) delete[] a; }

    template<typename U1, int N1,int M1, typename U2, int N2,int M2>
    fun friend constexpr operator*(const matrix<U1,N1,M1> &x, const matrix<U2,N2,M2> &y) -> matrix<std::common_type_t<U1, U2>>;

    [[no_unique_address]] size<N,M> sz;
private:
    std::conditional_t<dynamic<N,M>, T*,T[N * M]> a{};
public:

    fun one() -> matrix
    { return one<T,N,M>(row()); }

};

template<typename T,int N,int M>
fun consteval make(const T (&il)[N][M]) -> matrix<T,N,M>
{ return matrix<T,N,M>{ il }; }

template<typename T,int N,int M>
matrix(const T (&il)[N][M]) -> matrix<T,N,M>;

template<typename U,typename... R,int M_>
matrix(U const (&il)[M_],R const (&...ils)[M_]) -> matrix<std::common_type_t<U,R...>,1 + sizeof...(ils),M_>;

template<typename U1, int N1,int M1, typename U2, int N2,int M2>
requires std::common_with<U1,U2>
fun constexpr operator*(const matrix<U1,N1,M1> &x, const matrix<U2,N2,M2> &y)
-> std::conditional_t<(dynamic<N1,M1> or dynamic<N2,M2>),matrix<std::common_type_t<U1, U2>,dynamic_size,dynamic_size>,matrix<std::common_type_t<U1,U2>,N1,M2>>
{
using Ret = std::common_type_t<U1,U2>;
if constexpr(dynamic<N1,M1> or dynamic<N2,M2>) {
matrix<Ret> v(x.row(), y.cow(), {});
for(int i: iota(0, x.row())) {
for(int c: iota(0, x.cow())) {
for(int j: iota(0, y.cow())) {
v[i][j] += x[i][c] * y[c][j];
}
}
}
return v;
} else {
matrix<Ret,N1,M2> v;
for(int i : iota(0,x.row())) {
for(int c : iota(0,x.cow())) {
for(int j : iota(0,y.cow())) {
v[i][j] += x[i][c] * y[c][j];
}
}
}
return v;
}
}


}

using mat::matrix;

namespace xxx
{
    namespace mat
    {

        template<typename T,int N,int M>
        struct matrix;

        constexpr int dynamic_size = -1;

        template<int N,int M>
        struct size
        {
            constexpr size() = default;
            constexpr size(int,int){}
            constexpr static inline int n{ N },m{ M };
        };

        template<>
        struct size<dynamic_size,dynamic_size>
        {
            size(int n,int m) : n(n),m(m){}
            int n,m;
        };

        template<int N,int M>
        concept dynamic = N == dynamic_size and M == dynamic_size;

        template<typename T,int N = dynamic_size>
        fun constexpr one(int n) -> matrix<T,N,N>
    {
        if constexpr(dynamic<N,N>) {
        matrix<T, N, N> ret(n, n, {});
        for(int i: iota(0, n)) {
        ret[i][i] = 1;
    }
    return ret;
} else {
let ret = matrix<T,N,N>{};
for(int i: iota(0, n)) {
ret[i][i] = 1;
}
return ret;
}
}

template<typename T, std::integral I,int N = dynamic_size>
fun constexpr pow(const matrix<T,N,N> &v, I k) -> matrix<T,N,N>
{
auto a{ one<T,N>(v.row()) },tv{ v };
for(; k; k >>= 1) {
if(k & 1) {
a = a * tv;
}
tv = tv * tv;
}
return a;
}

template<typename T,int N = dynamic_size,int M = dynamic_size>
struct matrix
{

    matrix(int n, int m) requires dynamic<N,M> : a(new T[n * m]{}), sz(n,m)
    {}

    constexpr matrix() requires (not dynamic<N,M>) = default;

    matrix(int n, int m, const T &val) requires dynamic<N,M> : matrix(n, m)
    { std::ranges::fill_n(a, n * m, val); }

    explicit constexpr matrix(const T& val) requires (not dynamic<N,M>)
    {
        // std::ranges::fill_n(a,N * M,val);
        for(let i = 0,cei = row() * cow(); i != cei; ++i) {
            a[i] = val;
        }
    }

    constexpr matrix(const matrix &v) : sz(v.row(),v.cow())
    {
        if constexpr(dynamic<N,M>) {
            a = new T[v.row(),v.cow()];
            for(let i = 0,cei = v.row() * v.cow(); i != cei; ++i) {
                a[i] = v.a[i];
            }
        } else {
            std::ranges::copy(v.a,a);
        }
    }

    template<typename U>
    requires std::convertible_to<U, T>
    constexpr matrix(const matrix<U,N,M> &v) : matrix(v.row(),v.cow())
    {
        // std::ranges::copy_n(v.a, v.row() * v.cow(), a);
        for(let i = 0,cei = v.row() * v.cow(); i != cei; ++i) {
            a[i] = v[i];
        }
    }

    matrix(matrix &&v) noexcept requires dynamic<N,M> : a(v.a), sz(v.sz)
    { v.a = nullptr; }

    template<int N_,int M_>
    constexpr matrix(const T (&il)[N_][M_]) : sz(N_,M_)
    {
        T* it = a;
        for(auto& v : il) {
            std::ranges::copy(v,it);
            it += M;
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
    constexpr matrix(U const (&il)[M_],R const (&...ils)[M_]) : sz(sizeof...(ils) + 1,M_)
    {
        for(let i = 0; i != M_; ++i) {
            a[i] = il[i];
        }
        if constexpr (sizeof...(ils)) {
            make_matrix<1, M_, R...>(ils...);
        }
    }

    fun constexpr operator=(const matrix& v) -> matrix&
    {
        this->operator=<T,N,M>(v);
        return *this;
    }

    template<typename U,int N_,int M_>
    requires std::convertible_to<U,T>
    fun constexpr operator=(const matrix<U,N_,M_> &v) -> matrix& requires (dynamic<N,M> or (N == N_ and M == M_))
    {
        if constexpr(dynamic<N,M>) {
            sz = { v.row(),v.cow() };
            T *tmp = new T[row() * cow()];
            std::ranges::copy_n(v.a, row() * cow(), tmp);
            delete[] a;
            a = tmp;
        } else {
            std::ranges::copy(v.a,data());
        }
        return *this;
    }

    fun operator=(matrix &&v) noexcept -> matrix& requires dynamic<N,M>
    {
        sz = v.sz;
        std::swap(a,v.a);
        return *this;
    }

    fun constexpr operator[](int i) noexcept -> T*
    { return data() + (i * cow()); }

    fun constexpr operator[](int i) const noexcept -> const T*
    { return data() + (i * cow()); }

    fun constexpr operator^(std::integral auto n) -> matrix<T,N,M>
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
    { std::copy_n(std::istream_iterator<T>{ is },v.row() * v.cow(),v.a); return is; }

    fun friend operator<<(std::ostream& os,const matrix& v) -> std::ostream&
    {
        T const* it = v.a;
        for(int i : iota(0,v.row())) {
            std::ranges::copy_n(it,v.cow(),std::ostream_iterator<T>{ std::cout," " });
            std::cout << '\n';
            it += v.cow();
        }
        return os;
    }

    [[nodiscard]]
    fun constexpr row() const noexcept
    {
        return sz.n;
    }

    [[nodiscard]]
    fun constexpr cow() const noexcept
    {
        return sz.m;
    }

    template<std::invocable<T&,T&> Op>
    fun apply(int i,int j,Op op) -> void
    {
        let x = (*this)[i],y = (*this)[j];
        for(let _ in std::views::iota(0,cow())) {
            op(*x++,*y++);
        }
    }

    template<std::invocable<T&,T&> Op>
    fun tapply(int i,int j,Op op) -> void
    {
        let x = a + i,y = a + j;
        for(let _ in std::views::iota(0,row())) {
            op(*x,*y);
            x += cow(),y += cow();
        }
    }

    fun solve() -> int
    {
        let constexpr eps = 1e-6;
        let dr = 0;
        for(let i in std::views::iota(0,row())) {
            let ir = std::views::iota(i,row());
            let it = *std::ranges::find_if(ir,[](auto v){ return v; },[&](auto k){ return (*this)[k][i]; });
            while(it == row() and i + dr + 2 < cow()) {
                tapply(i,cow() - 1 - ++dr,std::ranges::swap);
                it = *std::ranges::find_if(ir,[](auto v){ return v; },[&](auto k){ return (*this)[k][i]; });
            }
            if(it == row()) {
                return -std::ranges::any_of(ir, [](auto v) { return std::abs(v) >= eps; },[&](auto i) { return (*this)[i][cow() - 1]; });
            }
            if(it != i) {
                apply(it,i,std::ranges::swap);
            }
            if(std::abs((*this)[i][i] - 1) >= eps) {
                for(let j in std::views::iota(i, cow()) | std::views::reverse) {
                    (*this)[i][j] /= (*this)[i][i];
                }
            }
            for(let k in iota(0,row()) | filter([&](auto k){ return k != i; })) {
                let const& coe = (*this)[k][i];
                apply(i,k,[coe](T& lhs,T& rhs) {
                    rhs -= lhs * coe;
                });
            }
        }
        return 1;
    }

    constexpr ~matrix()
    { if constexpr(dynamic<N,M>) delete[] a; }

    template<typename U1, int N1,int M1, typename U2, int N2,int M2>
    fun friend constexpr operator*(const matrix<U1,N1,M1> &x, const matrix<U2,N2,M2> &y) -> matrix<std::common_type_t<U1, U2>>;

    [[no_unique_address]] size<N,M> sz;
private:
    std::conditional_t<dynamic<N,M>, T*,std::array<T,N * M>> a;

    fun constexpr data() noexcept -> T*
    {
        if constexpr(dynamic<N,M>) {
            return a;
        } else {
            return a.data();
        }
    }

    [[nodiscard]]
    fun constexpr data() const noexcept -> const T*
    {
        if constexpr(dynamic<N,M>) {
            return a;
        } else {
            return a.data();
        }
    }

};

template<typename T,int N,int M>
fun consteval make(const T (&il)[N][M]) -> matrix<T,N,M>
{ return matrix<T,N,M>{ il }; }

template<typename T,int N,int M>
matrix(const T (&il)[N][M]) -> matrix<T,N,M>;

template<typename U,typename... R,int M_>
matrix(U const (&il)[M_],R const (&...ils)[M_]) -> matrix<std::common_type_t<U,R...>,1 + sizeof...(ils),M_>;

template<typename U1, int N1,int M1, typename U2, int N2,int M2>
requires std::common_with<U1,U2>
fun constexpr operator*(const matrix<U1,N1,M1> &x, const matrix<U2,N2,M2> &y)
-> std::conditional_t<(dynamic<N1,M1> or dynamic<N2,M2>),matrix<std::common_type_t<U1, U2>,dynamic_size,dynamic_size>,matrix<std::common_type_t<U1,U2>,N1,M2>>
{
using Ret = std::common_type_t<U1,U2>;
if constexpr(dynamic<N1,M1> or dynamic<N2,M2>) {
matrix<Ret> v(x.row(), y.cow(), {});
for(int i: iota(0, x.row())) {
for(int c: iota(0, x.cow())) {
for(int j: iota(0, y.cow())) {
v[i][j] += x[i][c] * y[c][j];
}
}
}
return v;
} else {
matrix<Ret,N1,M2> v;
for(int i : iota(0,x.row())) {
for(int c : iota(0,x.cow())) {
for(int j : iota(0,y.cow())) {
v[i][j] += x[i][c] * y[c][j];
}
}
}
return v;
}
}


}

using mat::matrix;
}