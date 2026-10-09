

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

#if __cplusplus >= 202002L
#include<format>
#include<ranges>
#include<bit>
#include<span>
#endif

#define fun auto
#define ref decltype(auto)
#define main fun main
#define let auto
#define cast static_cast
#define make_range(A) std::begin(A),std::end(A)

#if __cplusplus >= 202002L

#define list std::ranges::random_access_range auto
#define range std::ranges::range auto

#else

#define list auto

#endif

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

#if __cplusplus >= 202002L
using namespace std::views;

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
#endif

namespace fasti
{
    struct istream
    {
        template<std::integral T>
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
            mutable T val{ read() };
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

        template<std::integral T = int>
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
template<std::integral T>
using fiterator = fasti::istream::iterator<T>;


template<typename T = int,typename Exe = decltype(std::ranges::max),typename Proj = std::identity>
requires std::invocable<Exe,std::invoke_result_t<Proj,T>,std::invoke_result_t<Proj,T>>
struct st
{
    template<std::input_iterator It,std::sentinel_for<It> Se>
    st(It first_,Se end_,Exe exe = {},Proj proj = {}) requires std::convertible_to<std::iter_value_t<It>,T> : a(),exe(exe),proj(proj)
    {
        a.emplace_back();
        while(first_ != end_) {
            a[0].push_back(*first_++);
        }
        int lg = lg2[a[0].size()];
        a.resize(lg + 1);
        for(int p{ 1 }; p <= lg; ++p) {
            a[p].resize(a[0].size());
            for(int i{},off{ 1 << (p - 1) }; i + off < a[p].size(); ++i) {
                a[p][i] = exe(proj(a[p - 1][i]),proj(a[p - 1][i + (1 << (p - 1))]));
            }
        }
    }

    template<std::input_iterator It>
    st(It first_,int n,Exe exe = {},Proj proj = {}) requires std::convertible_to<std::iter_value_t<It>,T> : a(),exe(exe),proj(proj)
    {
        a.emplace_back();
        while(n) {
            a[0].push_back(*first_);
            if(--n) {
                ++first_;
            }
        }
        int lg = lg2[a[0].size()];
        a.resize(lg + 1);
        for(int p{ 1 }; p <= lg; ++p) {
            a[p].resize(a[0].size());
            for(int i{},off{ 1 << (p - 1) }; i + off < a[p].size(); ++i) {
                a[p][i] = exe(proj(a[p - 1][i]),proj(a[p - 1][i + (1 << (p - 1))]));
            }
        }
    }

    template<std::ranges::input_range R>
    explicit st(R&& r,Exe exe = {},Proj proj = {}) : st(std::ranges::begin(r),std::ranges::end(r),exe,proj){}

    [[nodiscard]]
    T reduce(int l,int r) const noexcept
    {
        int lg{ lg2[r - l + 1] };
        return exe(proj(a[lg][l]),proj(a[lg][r - (1 << lg) + 1]));
    }

    T operator()(int l,int r) const noexcept
    { return reduce(l,r); }

private :

    constexpr static int lg2cei = 104857;

    constexpr static std::array<int,lg2cei> lg2 = []() consteval {
        std::array<int,lg2cei> ret{};
        for(int i{ 2 }; i != ret.size(); ++i) {
            ret[i] = ret[i / 2] + 1;
        }
        return ret;
    }();

    std::vector<std::vector<T>> a;
    Exe exe;
    Proj proj;
};

constexpr int INF = std::numeric_limits<int>::max();
constexpr int64 INF64 = std::numeric_limits<int64>::max();

fun solve()
{
    int n,m;
    cin >> n >> m;
    st t{ fiterator<int>{},n,std::gcd<int,int> };
    while(m--) {
        int l,r;
        cin >> l >> r;
        println(t(--l,--r));
    }
}

main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}