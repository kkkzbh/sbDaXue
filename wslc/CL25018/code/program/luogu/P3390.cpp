

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
#define main fun main
#define let auto

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

#if __cplusplus >= 202002L
using namespace std::ranges::views;
#endif


template<typename T>
concept STD_array = requires(T array)
{
    typename T::value_type;
    { array[0] } -> std::same_as<std::add_lvalue_reference<typename T::value_type>>;
};

template<typename T>
concept Array = STD_array<T> or std::is_array_v<T>;

template<typename... Args>
fun print(const std::format_string<Args...> fmts,Args&&... args)
{
    std::cout << std::vformat(fmts.get(), std::make_format_args(args...));
}

template<typename T>
fun print(T&& arg)
{
    print("{}",arg);
}

fun println()
{
    print('\n');
}

template<typename... Args>
fun println(const std::format_string<Args...> fmts,Args&&... args)
{
    print(fmts,std::forward<Args>(args)...);
    println();
}

template<typename T>
fun println(T&& arg)
{
    println("{}",arg);
}

template<Array T>
fun scan(T& array,int n)
{
    if constexpr(std::is_array_v<T>)
    {
        std::copy_n(std::istream_iterator<std::remove_all_extents_t<T>>{ std::cin },n, std::ranges::begin(array) + 1);
    }
    else
    {
        std::copy_n(std::istream_iterator<typename T::value_type>{ std::cin },n,array.begin() + 1);
    }
}

template<Array T,std::integral... Args>
fun scan(T& array,int n,Args... args)
{
    for(int i : iota(1,n + 1))
    {
        scan(array[i],args...);
    }
}

template<typename... Args>
fun scan(Args&... args)
{
    (std::cin >> ... >> args);
}

namespace fasti
{
    struct istream
    {
        template<typename T>
        struct iterator
        {
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            fun friend operator==(iterator x,iterator y) { return !normal; }
            fun operator++() -> iterator&
            {
                if(lazy) {
                    cin >> val;
                } else {
                    lazy = true;
                }
                return *this;
            }
            fun operator++(int) -> iterator
            {
                iterator ret{ *this };
                ++*this;
                return ret;
            }
            fun operator*() const noexcept
            {
                if(lazy) {
                    cin >> val;
                    lazy = false;
                }
                return val;
            }
            fun operator->() const noexcept
            {
                if(lazy) {
                    cin >> val;
                    lazy = false;
                }
                return std::addressof(val);
            }
            mutable T val{ read<T>() };
            mutable bool lazy{};
        };

        constexpr static int n{ 640000 };
        static inline char buffer[n], *l{ buffer }, *r{ l };
        static istream cin;
        static inline bool normal{ true };

        operator bool()
        {
            return normal;
        }

        fun static get() -> char
        {
            if(l == r) {
                if(r = (l = buffer) + fread(buffer, 1, n, stdin); l == r) {
                    normal = false;
                    return *l;
                }
            }
            return *l++;
        }

        fun static get(char &c) -> istream&
        {
            c = get();
            return cin;
        }

        fun static peek() -> char
        {
            return *l;
        }

        fun static ignore()
        {
            ++l;
        }

        fun static unget()
        {
            --l;
        }

        template<typename T>
        fun static read() -> T
        {
            T ret;
            cin >> ret;
            return ret;
        }

        fun friend operator>>(istream& is,char& c) -> istream&
        {
            while(normal and isspace(c = get())) {}
            return is;
        }

#if __cplusplus >= 202002L
        template<std::integral T>
#else
        template<typename T>
#endif
        fun friend operator>>(istream& is, T& v) -> istream&
        {
            bool negative{};
            char c{};
            while(get(c) and isspace(c)) {}
            if(!normal) {
                return is;
            }
            if(c == '-') {
                negative = true;
                if(!get(c) or c < '0' or c > '9') {
                    return is;
                }
            }
            v = T{};
            do {
                v = v * 10 + (c ^ 48);
            }while(get(c) and c >= '0' and c <= '9');
            if(negative) {
                v = -v;
            }
            if(normal) {
                unget();
            }
            return is;
        }
    private:
        istream() = default;
    };

}
fasti::istream fasti::istream::cin;
auto& cin =  fasti::istream::cin;
template<typename T>
using fiterator = fasti::istream::iterator<T>;

constexpr int INF = std::numeric_limits<int>::max();
constexpr int64 INF64 = std::numeric_limits<int64>::max();
constexpr int MOD = 1000000000 + 7;

namespace mat
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
        auto a{ one<T>(v.n) },val(v);
        for(; k; k >>= 1) {
            if(k & 1) {
                a = a * val;
            }
            val = val * val;
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

        matrix(const matrix &v) : n(v.n), m(v.m)
        { std::ranges::copy_n(v.a, n * m, a); }

        template<typename U>
        requires std::convertible_to<U, T>
        matrix(const matrix<U> &v) : n(v.n), m(v.m)
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

        template<typename U1, typename U2>
        fun friend operator*(const matrix<U1> &x, const matrix<U2> &y) -> matrix<std::common_type_t<U1, U2>>
        {
            matrix<std::common_type_t<U1, U2>> v(x.n, y.m, {});
            for(int i: iota(0, x.n)) {
                for(int c: iota(0, x.m)) {
                    for(int j: iota(0, y.m)) {
                        v[i][j] += x[i][c] * y[c][j];
                        v[i][j] %= MOD;
                    }
                }
            }
            return v;
        }

        ~matrix()
        { delete[] a; }

        int n, m;
    private:
        T *a;
    public:

        fun one() -> matrix
        { return one<T>(n); }

    };

}

fun solve()
{
    int n;
    int64 k;
    cin >> n >> k;
    mat::matrix<int64> m(n, n);
    for(int i: iota(0, n)) {
        auto v = m[i];
        for(int j: iota(0, n)) {
            cin >> v[j];
        }
    }
    auto ret = pow(m, k);
    for(int i: iota(0, n)) {
        for(int j: iota(0, n)) {
            std::cout << ret[i][j] << ' ';
        }
        std::cout << '\n';
    }
}


main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}