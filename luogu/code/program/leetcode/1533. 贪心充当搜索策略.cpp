


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

#define fun auto constexpr
#define var auto
#define cast static_cast
#define range(A) A.begin(),A.end()

using int64 = long long;
using uint64 = unsigned long long;
using namespace std;

constexpr int INF{ 1000000000 + 520 };
constexpr int64 LNF { 66666666666666666 };

template<std::integral Tn,std::integral Td = Tn>
struct frac
{

    frac(Tn num,Td den) noexcept : num(num),den(den)
    {
        if(den < 0)
        {
            this->den = -den;
            this->num = -num;
        }
    }

    frac(Tn num) noexcept : num(num),den(1){}

    frac() noexcept requires std::default_initializable<Tn> and std::default_initializable<Td> = default;

    explicit operator double() const noexcept
    {
        return static_cast<double>(num) / den;
    }

    fun reduce() noexcept
    {
        Tn g{ std::gcd(num,den) };
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
        Tn g{ std::gcd(n.num,n.den) };
        if(n.den == g)
        {
            return os << n.num / g;
        }
        else
        {
            return os << n.num / g << '/' << n.den / g;
        }
    }

    Tn num{};
    Td den{ 1 };

};

template<typename T>
requires std::is_integral_v<T>
frac(T) -> frac<T>;

using decimal = frac<int64>;

std::unordered_map<int,int> mp;
fun dfs(int n) -> int
{
    if(n <= 2) {
        return n;
    }
    if(mp.contains(n)) {
        return mp[n];
    }
    int m2{ n & 1 };
    int m3{ n % 3 };
    return mp[n] = std::min(m2 + 1 + dfs(n >> 1),m3 + 1 + dfs(n / 3));
}

struct Solution
{
    int minDays(int n)
    {
        return dfs(n);
    }
};