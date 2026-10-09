

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
auto& cin =  fasti::istream::cin;

constexpr int INF = std::numeric_limits<int>::max();
constexpr int64 INF64 = std::numeric_limits<int64>::max();

template<typename T,typename Cmp = std::less<>,typename Proj = std::identity>
requires std::invocable<Proj,T> and
         std::invocable<Cmp,std::invoke_result_t<Proj,T>,std::invoke_result_t<Proj,T>> and
         std::convertible_to<std::invoke_result_t<Cmp,std::invoke_result_t<Proj,T>,std::invoke_result_t<Proj,T>>,bool>
struct mono_queue
{
    fun push(T v) noexcept
    {
        while(!que.empty() and cmp(proj(v),proj(que.back()))) {
            que.pop_back();
        }
        que.push_back(v);
    }

    fun pop(T v) noexcept
    {
        if(que.front() == v) {
            que.pop_front();
        }
    }

    [[nodiscard]]
    fun top() const noexcept
    {
        return proj(que.front());
    }

    [[nodiscard]]
    fun operator*() const noexcept
    {
        return top();
    }

    [[nodiscard]]
    fun empty() const noexcept -> bool
    {
        return que.empty();
    }

    [[nodiscard]]
    fun clear() noexcept
    {
        que.clear();
    }

    mono_queue() noexcept requires std::default_initializable<Cmp> and std::default_initializable<Proj> = default;

    explicit mono_queue(Cmp c) noexcept requires std::default_initializable<Proj> : mono_queue(c,{}) {}

    explicit mono_queue(Proj p) noexcept requires std::default_initializable<Cmp> : mono_queue({},p) {}

    mono_queue (Cmp c,Proj p) noexcept : cmp(c),proj(p){}

    Cmp cmp;
    Proj proj;

    std::deque<T> que;
};

template<typename T,typename Cmp,typename Proj>
fun make_mono_queue(Cmp cmp = {},Proj proj = {}) -> mono_queue<T,Cmp,Proj>
{
    return mono_queue<T,Cmp,Proj>{ cmp,proj };
}

fun solve()
{
    int n,m;
    cin >> n >> m;
    std::vector<int> a(n + 1);
    for(int i : iota(1,n + 1)) {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    let que = make_mono_queue<int>(std::less<>{},[&a](int i){ return a[i]; });
    int ans{};
    for(int i : iota(1,m)) {
        que.push(i);
        ans = std::max(ans,a[i] - std::min(*que,0));
    }
    for(int i : iota(m,n + 1)) {
        que.push(i);
        que.pop(i - m);
        ans = std::max(ans,a[i] - std::min(*que,a[i - m]));
    }
    println(ans);
}

main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}