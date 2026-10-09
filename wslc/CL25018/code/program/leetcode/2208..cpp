


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

#define fun auto
#define var auto
#define cast static_cast
#define range(A) A.begin(),A.end()

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;
using namespace std;

constexpr int INF{ 1000000000 + 520 };
constexpr int64 LNF { 66666666666666666 };\

template<typename T,typename Cmp = std::less<>,typename Proj = std::identity>
requires std::invocable<Proj,T> and std::invocable<Cmp,std::invoke_result_t<Proj,T>,std::invoke_result_t<Proj,T>> and
         std::convertible_to<std::invoke_result_t<Cmp,std::invoke_result_t<Proj,T>,std::invoke_result_t<Proj,T>>,bool>
struct priority_queue
{

    priority_queue() noexcept requires std::default_initializable<Cmp> and std::default_initializable<Proj> = default;
    explicit priority_queue(Cmp cmp) noexcept requires std::default_initializable<Proj> : priority_queue(cmp,{}){}
    explicit priority_queue(Proj proj) noexcept requires std::default_initializable<Cmp> : priority_queue({},proj){}
    priority_queue(Cmp cmp,Proj proj) noexcept : cmp(cmp),proj(proj){}

    template<std::input_iterator It,typename Se>
    requires requires(It it) { { *it } -> std::convertible_to<T>; } and std::sentinel_for<Se,It>
    priority_queue(It first_,Se end_,Cmp cmp = {},Proj proj = {}) : a(first_,end_),cmp(std::move(cmp)),proj(std::move(proj))
    { std::ranges::make_heap(a,this->cmp,this->proj); }

    template<std::ranges::input_range R>
    explicit priority_queue(R&& r,Cmp cmp = {},Proj proj = {})
            : priority_queue(std::ranges::begin(r),std::ranges::end(r),std::move(cmp),std::move(proj)){}

    fun push(const T& v) -> void
    { a.push_back(v); std::ranges::push_heap(a,cmp,proj); }

    fun push(T&& v) -> void
    { a.push_back(std::move(v)); std::ranges::push_heap(a,cmp,proj); }

    template<typename... Args>
    fun emplace(Args&&... args)
    { a.emplace_back(std::forward<Args>(args)...); std::ranges::push_heap(a,cmp,proj); }

    fun top() const noexcept -> T&
    { return a.front(); }

    [[nodiscard]]
    fun size() const noexcept -> int
    { return a.size(); }

    [[nodiscard]]
    fun empty() const noexcept -> bool
    { return a.empty(); }

    template<std::ranges::range R>
    requires std::ranges::input_range<R> and std::convertible_to<std::ranges::range_reference_t<R>,T>
    fun push_range(R&& r)
    {
        std::ranges::copy(r,std::back_inserter(a));
        std::ranges::make_heap(r,cmp,proj);
    }

    Cmp cmp;
    Proj proj;
    std::vector<T> a;
};

template<typename T,typename Cmp = std::less<>,typename Proj = std::identity>
fun make_priority_queue(Cmp cmp = {},Proj proj = {})
{ return ::priority_queue<T,Cmp,Proj>(std::move(cmp),std::move(proj)); }

template<typename T,std::input_iterator It,typename Se,typename Cmp = std::less<>,typename Proj = std::identity>
requires requires(It it) { { *it } -> std::convertible_to<T>; } and std::sentinel_for<Se,It>
fun make_priority_queue(It first_,Se end_,Cmp cmp = {},Proj proj = {})
{ return ::priority_queue<T,Cmp,Proj>(std::move(first_),std::move(end_),std::move(cmp),std::move(proj)); }

template<typename T,std::ranges::input_range R,typename Cmp = std::less<>,typename Proj = std::identity>
fun make_priority_queue(R&& r,Cmp cmp = {},Proj proj = {})
{ return ::priority_queue<T,Cmp,Proj>(r,cmp,proj); }

namespace std
{
    template<typename T,typename Container = std::vector<T>,typename Cmp = std::less<>,typename Proj = std::identity>
    fun make_priority_queue(Cmp cmp = {},Proj proj = {})
    {
        auto c = [&](const T& x,const T& y) -> bool {
            return std::invoke(cmp,std::invoke(proj,x),std::invoke(proj,y));
        };
        return std::priority_queue<T,Container,decltype(c)>{ c };
    }
}

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

    fun constexpr reduce() noexcept
    {
        Tn g{ std::gcd(num,den) };
        num /= g;
        den /= g;
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

using decimal = frac<int64>;

class Solution {
public:
    int halveArray(vector<int>& a)
    {
        std::priority_queue<double> que{ range(a) };
        double sum{ std::accumulate(range(a),double{}) / 2.0 };
        int ans{};
        while(sum > 0) {
            double val{ que.top() / 2.0 };
            que.pop();
            sum -= val;
            que.push(val);
            ++ans;
        }
        return ans;
    }
};