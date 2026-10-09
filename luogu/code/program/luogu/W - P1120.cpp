

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
#include<fstream>


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

fun solve()
{
    int n;
    cin >> n;
    let a = std::vector(n,0);
    for(auto& v : a) {
        cin >> v;
    }
    std::ranges::sort(a,std::greater<>{});
    int sum = std::reduce(a.begin(),a.end(),0);
    int mv = std::ranges::max(a);
    let next = std::vector(n,-1);
    for(int v{ a[0] },l{}; int i : iota(0,n)) {
        if(a[i] != v) {
            for(int j : iota(l,i)) {
                next[j] = i;
            }
            l = i;
            v = a[i];
        }
    }

    let vis = std::vector(n + 1,false);
    let dfs = [&, sum, f = [&, n](auto& self, int i, int l, int len, int cnt, int sum) mutable {
        // ?sz * len == sum --> len | sum
        if((sum + l) % len) {
            return false;
        }
        vis[i] = true;
        if(l == len) {
            if(cnt == n) {
                return true;
            }
            int it = std::distance(vis.begin(), std::ranges::find(vis,false));
            if(self(self, it, a[it], len, cnt + 1, sum - a[it])) {
                return true;
            }
            vis[i] = false;
            return false;
        }

        int lv{},rv{ n };
        while(lv != rv) {
            int mid = (lv + rv) / 2;
            if(l + a[mid] <= len) {
                rv = mid;
            } else {
                lv = mid + 1;
            }
        }

        for(int k{ lv }; k != -1 and k != n;) {
            if(vis[k]) {
                ++k;
                continue;
            }
            if(l + a[k] <= len) {
                if(self(self, k, l + a[k], len, cnt + 1, sum - a[k])) {
                    return true;
                }
                if(len - l == a[k]) {
                    break;
                }
            }
            k = next[k];
        }

        vis[i] = false;
        return false;

    }](int len) mutable {
        return f(f,0, a[0], len, 1, sum - a[0]);
    };

    for(int i : iota(mv,sum + 1)) {
        if(dfs(i)) {
            std::cout << i;
            break;
        }
    }

}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}