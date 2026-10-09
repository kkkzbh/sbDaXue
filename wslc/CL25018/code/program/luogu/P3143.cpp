

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>
#include<cmath>
#include<numeric>
#include<cstring>
#include<functional>
#include<string>
#include<bitset>
#include<unordered_map>
#include<deque>
#include<queue>
#include<optional>
#include<unordered_set>
#include<cassert>
#include<stack>

#define fun auto
#define var auto
#define ref decltype(auto)
#define cast static_cast
#define range(A) std::begin(A),std::end(A)

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;
using namespace std::views;

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;
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

namespace fasti
{
    struct istream
    {
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

        fun friend operator>>(istream& is,char& c) -> istream&
        {
            while(normal and isspace(c = get())) {}
            return is;
        }

        template<std::integral T>
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
var &cin =  fasti::istream::cin;

constexpr int INF{ 1000000000 + 520 };
constexpr int64 LNF { 66666666666666666 };

fun solve()
{
    int n,k;
    cin >> n >> k;
    std::vector<int> a(n);
    for(int i : iota(0,n)) {
        cin >> a[i];
    }
    std::ranges::sort(a);
    std::vector<int> left(n);
    left[0] = 1;
    for(int l{},r{ 1 }; r < n; ++r) {
        while(a[r] - a[l] > k) {
            ++l;
        }
        left[r] = std::max(left[r - 1],r - l + 1);
    }
    std::vector<int> right(n);
    right[n - 1] = 1;
    for(int l{ n - 2 },r{ n - 1 }; l >= 0; --l) {
        while(a[r] - a[l] > k) {
            --r;
        }
        right[l] = std::max(right[l + 1],r - l + 1);
    }
    int ans{ std::max(right[0],left[n - 1]) };
    for(int i{},cei{ n - 1 }; i != cei; ++i) {
        ans = std::max(left[i] + right[i + 1],ans);
    }
    println(ans);

}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}