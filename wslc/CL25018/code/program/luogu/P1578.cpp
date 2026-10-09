

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
#define var auto
#define lambda auto
#define ref decltype(auto)
#define main fun main
#define let constexpr static const var
#define type(T) decltype(T)
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
var &cin =  fasti::istream::cin;

let INF = 1000000000 + 520;
let LNF = 66666666666666666;

fun solve()
{
    int n,m,q;
    cin >> n >> m >> q;
    std::vector<std::vector<int>> a(n + 1);
    while(q--) {
        int x,y;
        cin >> x >> y;
        a[x].emplace_back(y);
    }
    std::ranges::for_each(a,[](list& v){
        std::ranges::sort(v);
        range ur{ std::ranges::unique(v) };
        v.erase(ur.begin(),ur.end());
    });
    std::vector<int> v(m + 2);
    v[m + 1] = -INF;
    int ans{};
    for(int i : iota(0,n + 1)) {
        ref ra{ a[i] };
        int it{};
        for(int j : iota(0,m + 1)) {
            if(it != ra.size() and ra[it] == j) {
                v[j] = 0;
                ++it;
            } else {
                v[j] += 1;
            }
        }
        std::stack<int,std::vector<int>> stk;
        for(int j : iota(0,m + 2)) {
            while(!stk.empty() and v[j] <= v[stk.top()]) {
                it = stk.top();
                stk.pop();
                int left{ (stk.empty() ? -1 : stk.top()) };
                left -= (left != -1);
                int right{ j + (j != m + 1) };
                int up{ i - v[it] };
                up -= (up != -1);
                int down{ i + 1 + (i + 1 != n + 1) };
                ans = std::max(ans,(right - left - 2) * (down - up - 2));
            }
            stk.push(j);
        }
    }
    println(ans);

}

main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}