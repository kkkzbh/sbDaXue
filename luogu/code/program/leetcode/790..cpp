

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

namespace omat
{

    template<typename T>
    struct matrix;

    template<typename T>
    fun one(int n) -> matrix<T>
    {
        matrix<T> ret(n, n, {});
        for(int i: std::views::iota(0, n)) {
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

        fun friend operator<<(std::ostream& os,const matrix& v)
        {
            T* it = v.a;
            for(int i : std::views::iota(0,v.n)) {
                std::ranges::copy_n(it,v.m,std::ostream_iterator<T>{ std::cout," " });
                std::cout << '\n';
                it += v.m;
            }
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
        for(int i: std::views::iota(0, x.n)) {
            for(int c: std::views::iota(0, x.m)) {
                for(int j: std::views::iota(0, y.m)) {
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
        for(int i: std::views::iota(0, n)) {
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

        matrix(int n, int m) requires dynamic<N,M> : a(new T[n * m]), sz(n,m)
        {}

        constexpr matrix() requires (!dynamic<N,M>) = default;

        constexpr matrix(int n,int m) requires (!dynamic<N,M>)
        {}

        matrix(int n, int m, const T &val) requires dynamic<N,M> : matrix(n, m)
        { std::ranges::fill_n(a, n * m, val); }

        constexpr matrix(int n,int m,const T& val) requires (!dynamic<N,M>) : matrix(val)
        {}

        explicit constexpr matrix(const T& val) requires (!dynamic<N,M>)
        { std::ranges::fill_n(a,N * M,val); }

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
        { std::ranges::copy_n(v.a, v.row() * v.cow(), a); }

        matrix(matrix &&v) noexcept requires dynamic<N,M> : a(v.a), sz(v.sz)
        { v.a = nullptr; }

        /*
         * this can not make constexpr or constexpr
         *
        matrix(std::initializer_list<std::initializer_list<T>> il) : matrix(il.size(), (il.begin())->size())
        {
            T *it = a;
            for(auto v: il) {
                it = std::ranges::copy(v, it).out;
            }
        }
        */

        template<int N_,int M_>
        consteval matrix(const T (&il)[N_][M_]) : sz(N_,M_)
        {
            T* it = a;
            for(auto& v : il) {
                std::ranges::copy(v,it);
                it += M;
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

        fun friend operator<<(std::ostream& os,const matrix& v)
        {
            T* it = v.a;
            for(int i : std::views::iota(0,v.row())) {
                std::ranges::copy_n(it,v.cow(),std::ostream_iterator<T>{ std::cout," " });
                std::cout << '\n';
                it += v.cow();
            }
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

/*
template<typename T>
matrix(std::initializer_list<std::initializer_list<T>> il) -> matrix<T,il.size(),il.begin()->size()>;
*/

    template<typename T,int N,int M>
    matrix(const T (&il)[N][M]) -> matrix<T,N,M>;

    template<typename U1, int N1,int M1, typename U2, int N2,int M2>
    requires std::common_with<U1,U2>
    fun constexpr operator*(const matrix<U1,N1,M1> &x, const matrix<U2,N2,M2> &y)
    -> std::conditional_t<(dynamic<N1,M1> or dynamic<N2,M2>),matrix<std::common_type_t<U1, U2>,dynamic_size,dynamic_size>,matrix<std::common_type_t<U1,U2>,N1,M2>>
    {
        using Ret = std::common_type_t<U1,U2>;
        constexpr int MOD = 1000000000 + 7;
        if constexpr(dynamic<N1,M1> or dynamic<N2,M2>) {
            matrix<Ret> v(x.row(), y.cow(), {});
            for(int i: std::views::iota(0, x.row())) {
                for(int c: std::views::iota(0, x.cow())) {
                    for(int j: std::views::iota(0, y.cow())) {
                        v[i][j] += x[i][c] * y[c][j];
                        v[i][j] %= MOD;
                    }
                }
            }
            return v;
        } else {
            matrix<Ret,N1,M2> v;
            for(int i : std::views::iota(0,x.row())) {
                for(int c : std::views::iota(0,x.cow())) {
                    for(int j : std::views::iota(0,y.cow())) {
                        v[i][j] += x[i][c] * y[c][j];
                        v[i][j] %= MOD;
                    }
                }
            }
            return v;
        }
    }

}

using mat::matrix;

class Solution {
public:
    int numTilings(int n) {
        let A = mat::make<int64>({
                                         { 1,1,2 },
                                         { 1,0,0 },
                                         { 0,1,1 },
                                 });
        let T1 = mat::make<int64>({
                                          { 2 },
                                          { 1 },
                                          { 1 },
                                  });

        let Tn = (A^(n - 1)) * T1;
        return Tn[1][0];
    }
};
