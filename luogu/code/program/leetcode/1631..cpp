

#include<bits/stdc++.h>

#define fun auto
#define let auto
#define in :

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

using namespace std;

template<typename T,typename Cmp = std::less<>,std::invocable<T> Proj = std::identity>
requires std::invocable<Cmp,std::invoke_result_t<Proj,T>,std::invoke_result_t<Proj,T>> and
         std::convertible_to<std::invoke_result_t<Cmp,std::invoke_result_t<Proj,T>,std::invoke_result_t<Proj,T>>,bool>
struct sblc
{

    sblc() noexcept requires std::default_initializable<Cmp> and std::default_initializable<Proj> = default;
    explicit sblc(Cmp&& cmp) : sblc(std::forward<Cmp>(cmp),{}){}
    sblc(Cmp&& cmp,Proj&& proj) noexcept : cmp(std::forward<Cmp>(cmp)),proj(std::forward<Proj>(proj)){}

    template<std::input_iterator It,std::sentinel_for<It> Se>
    requires requires(It it) { { *it } -> std::convertible_to<T>; }
    sblc(It first_,Se end_,Cmp cmp = {},Proj proj = {}) : a(first_,end_),cmp(std::move(cmp)),proj(std::move(proj))
    { std::ranges::make_heap(a,this->cmp,this->proj); }

    template<std::ranges::input_range R>
    explicit sblc(R&& r,Cmp cmp = {},Proj proj = {})
            : sblc(std::ranges::begin(r),std::ranges::end(r),std::move(cmp),std::move(proj)){}

    fun push(const T& v) -> void
    { a.push_back(v); std::ranges::push_heap(a,cmp,proj); }

    fun push(T&& v) -> void
    { a.push_back(std::move(v)); std::ranges::push_heap(a,cmp,proj); }

    template<typename... Args>
    fun emplace(Args&&... args)
    { a.emplace_back(std::forward<Args>(args)...); std::ranges::push_heap(a,cmp,proj); }

    fun top() const noexcept -> const T&
    { return a.front(); }

    fun pop() noexcept
    { std::ranges::pop_heap(a,cmp,proj); a.pop_back(); }

    [[nodiscard]]
    fun size() const noexcept -> int
    { return a.size(); }

    [[nodiscard]]
    fun empty() const noexcept -> bool
    { return a.empty(); }

    template<std::ranges::input_range R>
    requires std::convertible_to<std::ranges::range_reference_t<R>,T>
    fun push_range(R&& r)
    {
        std::ranges::copy(r,std::back_inserter(a));
        std::ranges::make_heap(r,cmp,proj);
    }

    Cmp cmp;
    Proj proj;
    std::vector<T> a;
};

template<typename T>
struct function_traits_base{};

template<typename Ret,typename... Args>
struct function_traits_base<std::function<Ret(Args...)>>
{
    using function_type = Ret(Args...);
    using return_type = Ret;
    using argument_tuple = std::tuple<Args...>;
    template<std::size_t N>
    using argument_type = std::tuple_element_t<N,argument_tuple>;
    constexpr static inline std::size_t arity = sizeof...(Args);
};

template<typename function> // 要求传入std::function类型
struct function_traits : function_traits_base<function>{};

template<typename Cmp>
explicit sblc(Cmp&& cmp) -> sblc<typename function_traits<decltype(std::function{ cmp })>::template argument_type<0>,Cmp,std::identity>;

template<typename Cmp,typename Proj>
sblc(Cmp&& cmp,Proj&& proj) -> sblc<typename function_traits<decltype(std::function{ proj })>::template argument_type<0>,Cmp,Proj>;

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();

#define print(STR,...) std::cout << std::format(STR,__VA_ARGS__)

class Solution {
public:
    int minimumEffortPath(std::vector<std::vector<int>>& a)
    {

        let n = int(a.size());
        let m = int(a.front().size());
        using pos = std::tuple<int,int>;
        let dis = std::vector(n,std::vector(m,INF));
        using node = std::tuple<pos,int>;
        let que = sblc{ std::greater{},[&](node v){ return std::get<1>(v); }};

        dis[0][0] = 0;
        que.emplace(pos{ 0,0 },dis[0][0]);

        let limit = [n,m](pos p) {
            let [x,y] = p;
            return x >= 0 and x < n and y >= 0 and y < m;
        };
        let vlimit = views::filter(limit);

        let constexpr dir = std::array {
                pos{ -1,0 },pos{ 0,1 },pos{ 1,0 },pos{ 0,-1 }
        };

        while(not que.empty()) {
            let [x,y] = std::get<0>(que.top());
            que.pop();
            for(let [mx,my] in dir | views::transform([x,y](pos p) -> pos{ return { std::get<0>(p) + x,std::get<1>(p) + y }; }) | vlimit) {
                if(let val = std::max(dis[x][y],std::abs(a[x][y] - a[mx][my])); val < dis[mx][my]) {
                    dis[mx][my] = val;
                    que.emplace(pos{ mx,my },val);
                }
            }
        }

        return dis[n - 1][m - 1];

    }
};

