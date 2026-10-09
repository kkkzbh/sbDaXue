

#include<bits/stdc++.h>

#define fun auto
#define let auto
#define in :

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

using namespace std::ranges::views;

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();



template<typename T,
        typename Cmp = std::less<>,
        std::invocable<T> Proj = std::identity,
        std::invocable<T> Iproj = std::identity>
requires requires(T v,Cmp cmp,Proj proj,Iproj iproj,std::hash<std::remove_reference_t<std::invoke_result_t<Iproj,T>>> hash) {
    { std::invoke(cmp,std::invoke(proj,v),
                  std::invoke(proj,v))} -> std::convertible_to<bool>;
    std::invoke(iproj,v);
    { std::invoke(hash,std::invoke(iproj,v)) } -> std::convertible_to<std::size_t>;
}
struct heap
{
    heap() requires std::default_initializable<Cmp> and std::default_initializable<Proj> = default;
    explicit heap(Cmp&& cmp,Proj&& proj = {},Iproj&& iproj = {}) : cmp{ std::forward<Cmp>(cmp) },proj{ std::forward<Proj>(proj) },iproj{ std::forward<Iproj>(iproj) } {}

    fun push(const T& v) -> void
    {
        let it = id.find(iproj(v));
        if(it == id.end()) {
            let pos = int(a.size());
            a.push_back(v);
            make_up(pos);
        } else if(let [key,i] = it; f(a[i],v)) {
            a[i] = v;
            make_up(i);
        }
    }

    fun push(T&& v) -> void
    {
        let it = id.find(iproj(v));
        if(it == id.end()) {
            let pos = int(a.size());
            a.push_back(std::move(v));
            make_up(pos);
        } else if(let [key,i] = *it; f(a[i],v)) {
            a[i] = v;
            make_up(i);
        }
    }

    template<typename... Args>
    fun emplace(Args&&... args) -> void
    { push(T{ std::forward<Args>(args)... }); }

    fun top() const -> const T&
    { return a.front(); }

    fun pop() -> void
    {
        id.erase(proj(top()));
        std::ranges::swap(a.front(),a.back());
        a.pop_back();
        make_down(0);
    }

    [[nodiscard]]
    fun empty() const -> int
    { return not size(); }

    [[nodiscard]]
    fun size() const -> int
    { return int(a.size()); }

private:

    fun f(const T& x,const T& y) const -> bool
    { return std::invoke(cmp,std::invoke(proj,x),std::invoke(proj,y)); }

    fun make_up(int i) -> void
    {
        let v = std::move(a[i]);
        let it = up(i);
        while(it != i and f(a[it],v)) {
            a[i] = std::move(a[it]);
            id[iproj(a[i])] = i;
            i = it;
            it = up(i);
        }
        a[i] = std::move(v);
        id[iproj(a[i])] = i;
    }

    fun make_down(int i) -> void
    {
        let v = std::move(a[i]);
        let it = left(i);
        let n = int(a.size());
        while(it < n) {
            if(let r = it + 1; r < n and f(a[it],a[r])) {
                ++it;
            }
            if(f(v,a[it])) {
                a[i] = std::move(a[it]);
                id[iproj(a[i])] = i;
                i = it;
                it = left(it);
            } else {
                break;
            }
        }
        a[i] = std::move(v);
        id[iproj(a[i])] = i;
    }

    fun constexpr static left(int i) -> int
    { return 2 * i + 1; }
    fun constexpr static right(int i) -> int
    { return left(i) + 1; }
    fun constexpr static up(int i) -> int
    { return (i - 1) / 2; }

    std::vector<T> a;
    std::unordered_map<std::remove_reference_t<std::invoke_result_t<Iproj,T>>,int> id;
    Cmp cmp;
    Proj proj;
    Iproj iproj;
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

template<typename Cmp = std::less<>,typename Proj = std::identity,typename Iproj = std::identity>
explicit heap(Cmp&& cmp,Proj&& proj = {},Iproj&& iproj = {}) -> heap<typename function_traits<decltype(std::function{ proj })>::template argument_type<0>,Cmp,Proj,Iproj>;



fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);

    int n,m;
    std::cin >> n >> m;
    let g = std::vector(n,std::vector<node>{});
    for(int a,b,w; let i in iota(0,m)) {
        std::cin >> a >> b >> w;
        --a,--b;
        g[a].emplace_back(b,w);
        g[b].emplace_back(a,w);
    }

    let path = dijkstra(0,g);
    if(path[n - 1] == -1) {
        std::print("{}",-1);
    } else {
        let stk = std::stack<int>{};
        let pos = n - 1;
        stk.push(pos);
        while(path[pos] != -1) {
            pos = path[pos];
            stk.push(pos);
        }
        while(not stk.empty()) {
            std::print("{} ", stk.top() + 1);
            stk.pop();
        }
    }

    return 0;
}


