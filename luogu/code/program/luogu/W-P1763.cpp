

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




template<typename Tn,typename Td = Tn>
requires (std::integral<Tn> or std::same_as<Tn,__int128>) and (std::integral<Td> or std::same_as<Td,__int128>)
struct frac
{

    constexpr frac(Tn num,Td den) noexcept : num(num),den(den)
    {
        if(den < 0)
        {
            this->den = -den;
            this->num = -num;
        }
    }

    constexpr frac(Tn num) noexcept : num(num),den(1){}

    constexpr frac() noexcept requires std::default_initializable<Tn> and std::default_initializable<Td> = default;

    explicit constexpr operator double() const noexcept
    {
        return static_cast<double>(num) / den;
    }

    explicit constexpr operator bool() const noexcept
    { return num; }

    [[nodiscard]]
    fun constexpr floor() const noexcept -> std::common_type_t<Tn,Td>
    {
        return num % den ? (num / den) - (num > 0 != den > 0) : num / den;
    }

    [[nodiscard]]
    fun constexpr ceil() const noexcept -> std::common_type_t<Tn,Td>
    {
        return num % den ? (num / den) + (num > 0 == den > 0) : num / den;
    }

    fun constexpr reduce() noexcept -> frac&
    {
        Tn g{ std::gcd(num,den) };
        num /= g;
        den /= g;
        return *this;
    }

    fun constexpr operator+=(const frac& n) noexcept -> frac&
    {
        num = num * n.den + n.num * den;
        den *= n.den;
        return *this;
    }

    fun constexpr operator-=(const frac& n) noexcept -> frac&
    {
        num = num * n.den - n.num * den;
        den *= n.den;
        return *this;
    }

    fun constexpr operator*=(const frac& n) noexcept -> frac&
    {
        num *= n.num;
        den *= n.den;
        return *this;
    }

    fun constexpr operator/=(const frac& n) noexcept -> frac&
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

    fun constexpr friend operator+(const frac& x,const frac& y) noexcept -> frac
    {
        frac ret{ x };
        ret += y;
        return ret;
    }

    fun constexpr friend operator-(const frac& x,const frac& y) noexcept -> frac
    {
        frac ret{ x };
        ret -= y;
        return ret;
    }

    fun constexpr friend operator*(const frac& x,const frac& y) noexcept  -> frac
    {
        frac ret{ x };
        ret *= y;
        return ret;
    }

    fun constexpr friend operator/(const frac& x,const frac& y) noexcept  -> frac
    {
        frac ret{ x };
        ret /= y;
        return ret;
    }

    fun constexpr friend operator-(const frac& x) noexcept -> frac
    {
        return frac{ -x.num,x.den };
    }

    fun constexpr friend operator==(const frac& x,const frac& y) noexcept -> bool
    {
        return x.num * y.den == y.num * x.den;
    }

    fun constexpr friend operator<=>(const frac& x,const frac& y) noexcept -> std::strong_ordering
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

constexpr int INF = std::numeric_limits<int>::max();
constexpr int64 INF64 = std::numeric_limits<int64>::max();

using f = frac<int64>;

fun solve()
{
    int a,b;
    std::cin >> a >> b;
    f v{ a,b };
    v.reduce();

    int level;
    let path = std::vector<int>{};
    let ans = std::vector<int>{};
    let ok = [&] {
        if(ans.empty() or path.back() < ans.back()) {
            ans = path;
        }
    };
    let constexpr ceil = 10000000;
    let ids = [&,fn = [&,ok](auto& self,f v,int den,int il) {
        if(il == level) {
            if(v) {
                return;
            }
            ok();
            return;
        }
        if(il + 1 == level) {
            v.reduce();
            if(v.num != 1 or !path.empty() and v.den == path.back()) {
                return;
            }
            path.push_back(v.den);
            ok();
            path.pop_back();
            return;
        }
        if(il + 2 == level) {
            v.reduce();
            auto [a,b] = v;
            int l = f{ 4 * b,a * a }.ceil(),r = std::min(2 * ceil / a,1LL * ceil * ceil / b);
            if(l > r) {
                return;
            }
            if(r - l <= 1000) {
                for(let k: iota(l, r + 1)) {
                    let delta2 = a * a * k * k - 4 * k * b;
                    if(delta2 <= 0) {
                        continue;
                    }
                    int64 delta = std::sqrt(static_cast<double128>(delta2)) + 2;
                    while(delta * delta > delta2) {
                        --delta;
                    }
                    if(delta * delta != delta2 or (k * a - delta) & 1) {
                        continue;
                    }
                    int64 x = (k * a - delta) / 2, y = (k * a + delta) / 2;
                    if(x != y and y <= ceil and !path.empty() and x > path.back()) {
                        path.push_back(x), path.push_back(y);
                        ok();
                        path.pop_back(), path.pop_back();
                    }
                }
                return;
            }
        }

        int l = (1 / v).ceil(),r = std::min<int>(((level - il) / v).floor(),ceil);
        if(l > r) {
            return;
        }
        for(let i : iota(l,r + 1)) {
            path.push_back(i);
            self(self,v - f{ 1,i },i,il + 1);
            path.pop_back();
        }

    }](f v) {
        for(level = 1; ; ++level) {
            fn(fn,v,1,0);
            if(!ans.empty()) {
                break;
            }
        }
    };

    ids(v);
    std::ranges::copy(ans,std::ostream_iterator<int>{ std::cout," " });

}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}