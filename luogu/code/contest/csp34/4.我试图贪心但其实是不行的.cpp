

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

    constexpr frac() noexcept = default;

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

    fun constexpr friend operator+(frac x,const frac& y) noexcept -> frac
    {
        x += y;
        return x;
    }

    fun constexpr friend operator-(frac x,const frac& y) noexcept -> frac
    {
        x -= y;
        return x;
    }

    fun constexpr friend operator*(frac x,const frac& y) noexcept  -> frac
    {
        x *= y;
        return x;
    }

    fun constexpr friend operator/(frac x,const frac& y) noexcept  -> frac
    {
        x /= y;
        return x;
    }

    fun constexpr friend operator-(frac x) noexcept -> frac
    {
        x.num = -x.num;
        return x;
    }

    fun constexpr friend operator==(const frac& x,const frac& y) noexcept -> bool
    {
        return x.num * y.den == y.num * x.den;
    }

    fun constexpr friend operator>(const frac& x,const frac& y) noexcept
    {
        return x.num * y.den > y.num * x.den;
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
frac(T) -> frac<T>;

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();

using f = frac<int64>;

struct repository
{
    int dp;
    int cp;
    std::vector<int> a;
};

fun solve()
{
    int n,m,v;
    std::cin >> n >> m >> v;
    let rep = std::vector(n,repository{});
    let vis = std::vector(n,false);
    for(int i{}; i != n; ++i) {
        std::cin >> rep[i].dp >> rep[i].cp;
    }
    for(int i{}; i != m; ++i) {
        int a,t;
        std::cin >> a >> t;
        rep[t].a.push_back(a);
    }
    for(int i{}; i != n; ++i) {
        std::sort(rep[i].a.begin(),rep[i].a.end());
    }
    let select = [&,n,v] {
        int ret{ -1 };
        let q = f{ -INF };
        int ret2{ -1 };
        int c{ INF };
        for(int i{}; i != n; ++i) {
            if(!rep[i].a.empty()) {
                let cost = !vis[i] * rep[i].dp + rep[i].cp;
                let tmp = f{ rep[i].a.back() - cost,cost };
                if(cost < v) {
                    if(tmp > q) {
                        ret = i;
                        q = tmp;
                    }
                } else {
                    if(cost < c) {
                        ret2 = i;
                        c = cost;
                    }
                }
            }
        }
        if(ret == -1) {
            return ret2;
        } else if(ret2 == -1) {
            return ret;
        } else if(c < q.den) {
            return ret;
        } else {
            return ret2;
        }
    };
    int ans{};
    while(v > 0) {
        int i = select();
        int cost = !vis[i] * rep[i].dp + rep[i].cp;
        ans += cost;
        v -= rep[i].a.back() - cost;
        rep[i].a.pop_back();
        vis[i] = true;
    }

    std::cout << ans;

}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::invoke(solve);
}