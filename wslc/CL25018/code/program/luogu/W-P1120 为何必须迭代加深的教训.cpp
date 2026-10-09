

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
    f val{ a,b };
    val.reduce();
    let path = std::vector<int>{};
    let ans = std::vector<int>{};
    constexpr int ceil = 10000000 + 1;
    enum
    {
        normal,
        over,
        error,
    };
    let dfs = [&, fn = [&](auto& self,f v,int den) {
        if(!ans.empty() and path.size() == ans.size() and v != 0) {
            return over;
        }
        if(!ans.empty() and path.size() + 1 == ans.size()) {
            v.reduce();
            if(v.num == 1 and v.den > path.back() and std::ranges::none_of(ans,[den = v.den](int v){ return v == den; })) {
                path.push_back(v.den);
                if(ans.empty() or path.size() < ans.size() or path.back() < ans.back()) {
                    ans = path;
                }
                path.pop_back();
                return normal;
            }
        }
        if(!ans.empty() and path.size() + 2 == ans.size()) {
            v.reduce();
            int64 l = (4 * v.den) / (v.num* v.num) + 1,r = std::min(2LL * ceil / v.num,1LL * ceil * ceil / v.den);
            if(r <= 1000) {
                for(let z: iota(l, r + 1)) {
                    auto [a, b] = v;
                    let d2 = (a * a * z * z) - 4 * b * z;
                    int64 d = std::sqrt(d2) + 2;
                    while(d * d > d2) {
                        --d;
                    }
                    if(d * d != d2 or a * z - d % 2) {
                        continue;
                    }
                    let x = (a * z - d) / 2, y = (a * z + d) / 2;
                    if(x != y and x > path.back() and y < ceil) {
                        path.push_back(x);
                        path.push_back(y);
                        if(ans.empty() or path.size() < ans.size() or path.back() < ans.back()) {
                            ans = path;
                        }
                        path.pop_back();
                        path.pop_back();
                    }
                    return normal;
                }
                return error;
            }
        }
        if(v == 0) {
            if(ans.empty() or path.size() < ans.size() or path.back() < ans.back()) {
                ans = path;
            }
            return normal;
        }
        int l = std::max<int>(den + 1,(1 / v).ceil());
        int r = ceil - 1;
        if(!ans.empty()) {
            r = std::min<int>(r,((1 / v) * (ans.size() - path.size())).floor());
        }
        for(int i : iota(std::min(l,r + 1),r + 1)) {
            if(!ans.empty() and i > ((1 / v) * (ans.size() - path.size())).floor()) {
                break;
            }
            f tv{ 1,i };
            f nv = v - tv;
            if(nv >= 0) {
                path.push_back(i);
                let ret = self(self,nv,i);
                path.pop_back();
                if(ret == over) {
                    return over;
                }
            }
        }
        return error;
    }](f v) {
        for(int i : iota(2,ceil)) {
            if(!ans.empty() and i > ((1 / v) * (ans.size() - path.size())).floor()) {
                break;
            }
            f tv{ 1,i };
            f nv = v - tv;
            if(nv >= 0) {
                path.push_back(i);
                let ret = fn(fn,nv,i);
                path.pop_back();
            }
        }
    };

    dfs(val);
    std::ranges::copy(ans,std::ostream_iterator<int>{ std::cout," " });
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}