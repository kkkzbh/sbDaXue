template<typename T>
struct matrix;

template<typename T>
auto one(int n) -> matrix<T>
{
    matrix<T> ret(n, n, {});
    for(int i : std::views::iota(0, n)) {
        ret[i][i] = T{1};
    }
    return ret;
}

template<typename T, std::integral I>
auto pow(const matrix<T> &v, I k) -> matrix<T>
{
    auto a{one<T>(v.n)}, tv{v};
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
    {
    }

    matrix(int n, int m, const T &val) : matrix(n, m)
    {
        std::ranges::fill_n(a, n * m, val);
    }

    matrix(const matrix &v) : matrix(v.n, v.m)
    {
        std::ranges::copy_n(v.a, n * m, a);
    }

    template<typename U>
        requires std::convertible_to<U, T>
    matrix(const matrix<U> &v) : matrix(v.n, v.m)
    {
        std::ranges::copy_n(v.a, n * m, a);
    }

    matrix(matrix &&v) noexcept: a(v.a), n(v.n), m(v.m)
    {
        v.a = nullptr;
    }

    template<int N_, int M_>
    constexpr matrix(const T (&il)[N_][M_]) : matrix(N_, M_)
    {
        T *it = a;
        for(auto &v : il) {
            std::ranges::copy(v, it);
            it += M_;
        }
    }

    template<int I, int M_, typename U>
    auto constexpr make_matrix(U const (&il)[M_])
    {
        auto d = I * M_;
        for(auto i = 0; i != M_; ++i) {
            a[d + i] = il[i];
        }
    }

    template<int I, int M_, typename U, typename... R>
    auto constexpr make_matrix(U const (&il)[M_], R const (&... ils)[M_])
    {
        auto d = I * M_;
        for(auto i = 0; i != M_; ++i) {
            a[d + i] = il[i];
        }
        make_matrix<I + 1, M_, R...>(ils...);
    }

    template<typename U, typename... R, int M_>
    constexpr matrix(U const (&il)[M_], R const (&... ils)[M_]) : matrix(sizeof...(ils) + 1, M_)
    {
        for(auto i = 0; i != M_; ++i) {
            a[i] = il[i];
        }
        if constexpr(sizeof...(ils)) {
            make_matrix<1, M_, R...>(ils...);
        }
    }

    template<typename U>
    auto operator=(const matrix<U> &v) -> matrix &
    {
        n = v.n;
        m = v.m;
        T *tmp = new T[n * m];
        std::ranges::copy_n(v.a, n * m, tmp);
        a = tmp;
        return *this;
    }

    auto operator=(matrix &&v) noexcept -> matrix &
    {
        n = v.n;
        m = v.m;
        a = v.a;
        v.a = nullptr;
        return *this;
    }

    auto operator[](int i) noexcept -> T * { return a + (i * m); }

    auto operator[](int i) const noexcept -> const T * { return a + (i * m); }

    auto operator^(std::integral auto p) -> matrix<T> { return pow(*this, p); }

    auto operator*=(const T &val)
    {
        std::ranges::transform(a, a + n * m, a, [&val](const T &v) -> T { return v * val; });
    }

    auto operator*=(matrix const &v)
    {
        return *this = *this * v;
    }

    auto operator%=(const T &val)
    {
        std::ranges::transform(a, a + n * m, a, [&val](const T &v) -> T { return v % val; });
    }

    auto operator>>=(const matrix &v) -> matrix & { return *this = v * *this; }

    auto operator<<=(const matrix &v) -> matrix & { return *this = *this * v; }


    auto friend operator>>(std::istream &is, matrix &v) -> std::istream &
    {
        std::copy_n(std::istream_iterator<T>{is}, v.n * v.m, v.a);
        return is;
    }

    auto friend operator<<(std::ostream &os, const matrix &v) -> std::ostream &
    {
        T *it = v.a;
        for(int i : std::views::iota(0, v.n)) {
            std::ranges::copy_n(it, v.m, std::ostream_iterator<T>{std::cout, " "});
            std::cout << '\n';
            it += v.m;
        }
        return os;
    }

    template<std::invocable<T&, T&> Op>
    auto apply(int i, int j, Op op) -> void
    {
        auto x = (*this)[i], y = (*this)[j];
        for(auto _ : std::views::iota(0, m)) {
            op(*x++, *y++);
        }
    }

    template<std::invocable<T&, T&> Op>
    auto tapply(int i, int j, Op op) -> void
    {
        auto x = a + i, y = a + j;
        for(auto _ : std::views::iota(0, n)) {
            op(*x, *y);
            x += m, y += m;
        }
    }

    auto solve() -> std::tuple<bool, int, int>
    {
        auto constexpr NOTE =
                "返回是否有解,rank,使用方程个数"
                "如果无解，第三个参数无意义";
        auto constexpr eps = 1e-6;
        auto dr = 0, cnt = 0;
        for(auto i : std::views::iota(0, std::min(n, m - 1))) {
            auto ir = std::views::iota(i, n);
            auto it = *std::ranges::find_if(ir, [](auto const &v) { return bool(v); },
                                            [&](auto k) { return (*this)[k][i]; });
            while(it == n and i + dr + 2 < m) {
                tapply(i, m - 1 - ++dr, std::ranges::swap);
                it = *std::ranges::find_if(ir, [](auto const &v) { return bool(v); },
                                           [&](auto k) { return (*this)[k][i]; });
            }
            cnt = std::max(cnt, it);
            if(it == n) {
                return {
                    std::ranges::any_of(ir, [](auto const &v) {
                                            if constexpr(std::floating_point<T>) {
                                                return std::abs(v) >= eps;
                                            } else {
                                                return bool(v);
                                            }
                                        }, [&](auto i) { return (*this)[i][m - 1]; }),
                    i + 1, cnt + 1
                };
            }
            if(it != i) {
                apply(it, i, std::ranges::swap);
            }
            if(std::abs((*this)[i][i] - 1) >= eps) {
                for(auto j : std::views::iota(i, m) | std::views::reverse) {
                    (*this)[i][j] /= (*this)[i][i];
                }
            }
            for(auto k : std::views::iota(0, n) | filter([&](auto k) { return k != i; })) {
                auto const &coe = (*this)[k][i];
                apply(i, k, [coe](T &lhs, T &rhs) {
                    rhs -= lhs * coe;
                });
            }
        }
        return {true, m - 1, cnt + 1};
    }

    ~matrix()
    {
        delete[] a;
    }

    template<typename U1, typename U2>
    auto friend operator*(const matrix<U1> &x, const matrix<U2> &y) -> matrix<std::common_type_t<U1, U2> >;

    int n, m;

private:
    T *a;

public:
    auto one() -> matrix { return one<T>(n); }
};

template<typename U, typename... R, int M_>
matrix(U const (&il)[M_], R const (&... ils)[M_]) -> matrix<std::common_type_t<U, R...> >;

template<typename U1, typename U2>
auto operator*(const matrix<U1> &x, const matrix<U2> &y) -> matrix<std::common_type_t<U1, U2> >
{
    matrix<std::common_type_t<U1, U2> > v(x.n, y.m, {});
    for(int i : std::views::iota(0, x.n)) {
        for(int c : std::views::iota(0, x.m)) {
            for(int j : std::views::iota(0, y.m)) {
                v[i][j] += x[i][c] * y[c][j];
            }
        }
    }
    return v;
}

template<typename T>
    requires std::integral<T> or std::same_as<T, __int128>
auto xor_solve(std::vector<std::vector<T> > &a) -> std::tuple<bool, int, int>
{
    auto constexpr NOTE =
            "返回 是否有解 rank 使用方程个数"
            "如果无解,后续参数无意义";

    auto const &n = int(a.size());
    auto const &m = int(a[0].size());
    if(n < m - 1) {
        return {false, {}, {}};
    }
    auto cnt = 0;
    for(auto j : std::views::iota(0, m - 1)) {
        auto rv = std::views::iota(j, n);
        auto it = *std::ranges::find(rv, true, [&](auto i) { return bool(a[i][j]); });
        if(it == n) {
            return {false, {}, {}};
        }
        if(it != j) {
            std::ranges::swap(a[it], a[j]);
        }
        cnt = std::ranges::max(cnt, it);
        for(auto k : std::views::iota(0, n) | filter([&](auto k) { return k != j and bool(a[k][j]); })) {
            for(auto i : std::views::iota(0, m)) {
                a[k][i] = a[k][i] ^ a[j][i];
            }
        }
    }
    return {true, m - 1, cnt + 1};
}

template<std::size_t N>
auto bit_xor_solve(std::vector<std::bitset<N> > &a, int m) -> std::tuple<int, int, int>
{
    auto constexpr NOTE =
            "返回值解释"
            "1.是否有解 "
            "2.rank"
            "3.方程使用个数"
            "若无解 后续参数无意义"

            "参数解释"
            "a: 要传入的方程组"
            "m: 传入的变量个数,默认第m列为增广矩阵列";

    auto n = int(a.size());
    if(n < m) {
        return {false, {}, {}};
    }
    auto cnt = 0;
    for(auto j : std::views::iota(0, m)) {
        auto it = std::invoke([&] {
            for(auto i : std::views::iota(j, n)) {
                if(bool(a[i][j])) {
                    return i;
                }
            }
            return n;
        });
        if(it == n) {
            return {false, {}, {}};
        }
        cnt = std::max(cnt, it);
        if(it != j) {
            std::ranges::swap(a[j], a[it]);
        }
        for(auto i : std::views::iota(0, n) | filter([&](auto i) { return i != j and bool(a[i][j]); })) {
            a[i] ^= a[j];
        }
    }
    return {true, m, cnt + 1};
}

struct linera_basis_fn
{
    template<typename T>
    requires std::integral<T> or std::same_as<T, __int128>
    [[nodiscard]]
    auto static increment(std::vector<T> const& a,int m) -> std::pair<std::vector<T>,bool>
    {
        using value_type = T;
        auto ret = std::vector(m + 1,value_type{});
        auto zero = false;
        auto insert = [&ret,&zero,m](value_type val) {
            for(auto i : std::views::iota(0,m + 1) | std::views::reverse | std::views::filter([&val](auto i){ return bool(val >> i); })) {
                if(ret[i]) {
                    val ^= ret[i];
                } else {
                    ret[i] = val;
                    return;
                }
            }
            zero = true;
        };
        std::ranges::for_each(a,insert);
        return std::make_pair(ret,zero);
    }

    template<std::size_t N>
    auto static guess(std::vector<std::bitset<N>>& a,int m) -> int
    {
        auto n = int(a.size());
        auto rank = 0;
        auto const bit = std::bitset<N>{ 1ULL << (m - 1) };

        for(auto i : std::views::iota(0,m + 1)) {
            auto ir = std::views::iota(rank,n);
            auto it = *std::ranges::find_if(ir,[](auto v){ return bool(v); },[&a,&bit,i,m](auto k){ return (a[k] << i & bit).test(m - 1); });
            if(it == n) {
                continue;
            }
            if(it != rank) {
                std::ranges::swap(a[it],a[rank]);
            }
            for(auto k : std::views::iota(0,n) | std::views::filter([&a,rank,&bit,i,m](auto k){ return k != rank and (a[k] << i & bit).test(m - 1); })) {
                a[k] ^= a[rank];
            }
            if(++rank == n) {
                break;
            }
        }
        return rank;
    }

    template<typename T>
    requires std::integral<T> or std::same_as<T, __int128>
    auto static gauss(std::vector<T>& a,int m) noexcept -> int
    {
        auto n = int(a.size());
        auto rank = 0;
        auto const bit = T{ 1 } << (m - 1);
        for(auto i : std::views::iota(0,m + 1)) {
            auto ir = std::views::iota(rank,n);
            auto it = *std::ranges::find_if(ir,[](auto v){ return bool(v); },[&a,bit,i](auto k){ return a[k] << i & bit; });
            if(it == n) {
                continue;
            }
            if(it != rank) {
                std::ranges::swap(a[it],a[rank]);
            }
            for(auto k : std::views::iota(0,n) | std::views::filter([&a,rank,bit,i](auto k){ return k != rank and bool(a[k] << i & bit); })) {
                a[k] ^= a[rank];
            }
            if(++rank == n) {
                break;
            }
        }
        return rank;
    }
};

auto constexpr inline linera_basis = linera_basis_fn{};