

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

#define fun auto

using int8 = char;
using uint8 = unsigned char;
using int32 = int;
using uint32 = unsigned int;
using uint = uint32;
using int64 = long long;
using uint64 = unsigned long long;
using namespace std::views;

template<typename T>
concept STD_array = requires(T array)
{
    typename T::value_type;
    { array[0] } -> std::same_as<std::add_lvalue_reference<typename T::value_type>>;
};

template<typename T>
concept Array = STD_array<T> or std::is_array_v<T>;

#ifdef __GNUC__
template<typename T>
concept Integral = std::is_integral_v<T> or std::is_same_v<T,__int128>;
#else
template<typename T>
concept Integral = std::is_integral_v<T>;
#endif

template<typename... Args>
fun print(const std::format_string<Args...> fmts,Args&&... args)
{
    std::cout << std::vformat(fmts.get(), std::make_format_args(args...));
}

template<typename... Args>
fun println(const std::format_string<Args...> fmts,Args&&... args)
{
    std::cout << std::vformat(fmts.get(), std::make_format_args(args...)) << '\n';
}

fun println()
{
    std::cout << '\n';
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

template<Array T,Integral... Args>
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

template<Integral T>
struct frac
{

    frac(T num,T den) noexcept : num(num),den(den)
    {
        if(den < 0)
        {
            this->den = -den;
            this->num = -num;
        }
    }

    frac(T num) noexcept : num(num),den(1){}

    frac() noexcept requires std::default_initializable<T> = default;

    explicit operator double() const noexcept
    {
        return static_cast<double>(num) / den;
    }

    fun reduce() noexcept
    {
        T g{ std::gcd(num,den) };
        num /= g;
        den /= g;
    }

    fun operator+=(const frac& n) noexcept -> frac&
    {
        num = num * n.den + n.num * den;
        den *= n.den;
        return *this;
    }

    fun operator-=(const frac& n) noexcept -> frac&
    {
        num = num * n.den - n.num * den;
        den *= n.den;
        return *this;
    }

    fun operator*=(const frac& n) noexcept -> frac&
    {
        num *= n.num;
        den *= n.den;
        return *this;
    }

    fun operator/=(const frac& n) noexcept -> frac&
    {
        num *= n.den;
        den *= n.num;
        if(den < 0)
        {
            num = -num;
            den = -den;
        }
        return *this;
    }

    fun friend operator+(const frac& x,const frac& y) noexcept -> frac
    {
        frac ret{ x };
        ret += y;
        return ret;
    }

    fun friend operator-(const frac& x,const frac& y) noexcept -> frac
    {
        frac ret{ x };
        ret -= y;
        return ret;
    }

    fun friend operator*(const frac& x,const frac& y) noexcept  -> frac
    {
        frac ret{ x };
        ret *= y;
        return ret;
    }

    fun friend operator/(const frac& x,const frac& y) noexcept  -> frac
    {
        frac ret{ x };
        ret /= y;
        return ret;
    }

    fun friend operator-(const frac& x) noexcept -> frac
    {
        return frac{ -x.num,x.den };
    }

    fun friend operator==(const frac& x,const frac& y) noexcept -> bool
    {
        return x.num * y.den == y.num * x.den;
    }

    fun friend operator<=>(const frac& x,const frac& y) noexcept -> std::strong_ordering
    {
        return x.num * y.den <=> y.num * x.den;
    }

    fun friend operator<<(std::ostream& os,const frac& n) noexcept -> std::ostream&
    {
        T g{ std::gcd(n.num,n.den) };
        if(n.den == g)
        {
            return os << n.num / g;
        }
        else
        {
            return os << n.num / g << '/' << n.den / g;
        }
    }

    T num{};
    T den{ 1 };

};

template<Integral T>
frac(T) -> frac<T>;

constexpr static int INF{ 0x3f3f3f3f };

using decimal = frac<int64>;

fun solve()
{
    int x,y,r,vx,vy;
    int lx,ly,rx,ry;
    scan(x,y,r,vx,vy,lx,ly,rx,ry);
    decimal t{};
    if(vx > 0)
    {   // (x - r) + k * vx == lx
        t = std::max(t,decimal{ lx - x + r,vx });
    }
    else if(vx < 0)
    {   // (x + r) + k * vx == rx
        t = std::max(t,decimal{ rx - x - r,vx });
    }
    if(vy > 0)
    {
        t = std::max(t,decimal{ ly - y + r,vy });
    }
    else if(vy < 0)
    {
        t = std::max(t,decimal{ ry - y - r,vy });
    }
    if(x + t * vx - r >= lx and x + t * vx + r <= rx and y + t * vy - r >= ly and y + t * vy + r <= ry)
    {
        println("Yes");
    }
    else
    {
        println("No");
    }
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while(t--)
    {
        std::invoke(solve);
    }
}