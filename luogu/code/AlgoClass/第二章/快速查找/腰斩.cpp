

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

struct clock
{
    using time_t = decltype(std::chrono::high_resolution_clock::now());

    fun static start()
    { start_ = std::chrono::high_resolution_clock::now(); }
    fun static end()
    { end_ = std::chrono::high_resolution_clock::now(); }
    fun static time()
    { return std::chrono::high_resolution_clock::now(); }

    static time_t start_;
    static time_t end_;
};

struct median3_fn
{
    template<std::random_access_iterator It>
    fun static operator()(It first,It end) -> It
    {
        let n = std::ranges::distance(first,end);
        end = std::ranges::prev(end);
        let mid = std::ranges::next(first,n / 2);
        let arr = std::array{ *first,*mid,*end };
        std::ranges::sort(arr);
        std::tie(*first,*mid,*end) = arr;
        std::iter_swap(mid,end);
        return end;
    }
};

let static inline median3 = median3_fn{};

struct two_way_partition_fn
{

    template<std::random_access_iterator It,typename F>
    requires std::sortable<It,F>
    fun static two_way_partition(It first,It end,F f) -> It
    {
        let pivot = *end;
        let it = end;
        end = std::ranges::prev(end);
        while(first < end) {
            if(f(*first,pivot)) {
                ++first;
            } else if(f(pivot,*end)) {
                --end;
            } else {
                std::ranges::iter_swap(first,end);
            }
        }
        std::ranges::iter_swap(first,it);
        return first;
    };

    template<std::random_access_iterator It,typename Cmp = std::less<>,typename Proj = std::identity>
    requires std::sortable<It,Cmp,Proj>
    fun static operator()(It first,It end,Cmp cmp = {},Proj proj = {}) -> It
    {
        let f = [&] <typename T,typename U> (T&& lhs,U&& rhs) -> bool {
            return std::invoke(cmp,
                               std::invoke(proj,std::forward<T>(lhs)),
                               std::invoke(proj,std::forward<U>(rhs)));
        };
        return two_way_partition(first,end,f);
    }
};

let static inline two_way_partition = two_way_partition_fn{};;

struct quick_select_
{

    template<std::random_access_iterator It,
            typename F,
            std::invocable<It,It> sp_t = decltype(median3),
            std::invocable<It,It> dv_t = decltype(two_way_partition)>
    requires std::sortable<It,F>
    fun constexpr static quick_select(It first,It end,std::integral auto k,F f,sp_t sp,dv_t dv) -> It // NOLINT
    {
        let n = std::ranges::distance(first,end);
        if(n < 100) {
            std::ranges::sort(first,end);
            return std::ranges::next(first,k);
        }
        let ed = sp(first,end);
        let it = dv(first,ed,f);
        let i = std::ranges::distance(first,it);
        if(i == k) {
            return it;
        } else if(i < k) {
            return quick_select(first,it,k,f,sp,dv);
        } else {
            return quick_select(std::ranges::next(it),end,k - i - 1,f,sp,dv);
        }
    }

    template<std::random_access_iterator It,std::sentinel_for<It> St,
            typename Cmp = std::less<>,typename Proj = std::identity,
            std::invocable<It,St> sp_t = decltype(median3),
            std::invocable<It,St> dv_t = decltype(two_way_partition)>
    requires std::sortable<It,Cmp,Proj>
    fun constexpr static operator()(It first,St sentry,std::integral auto k,Cmp cmp = {},Proj proj = {},sp_t sp = {},dv_t dv = {}) -> It
    {
        let f = [&] <typename T,typename U> (T&& lhs,U&& rhs) -> bool {
            return std::invoke(cmp,
                               std::invoke(proj,std::forward<T>(lhs)),
                               std::invoke(proj,std::forward<U>(rhs)));
        };
        return quick_select(first,std::ranges::next(first,sentry),k,f,sp,dv);
    }

};
let inline quick_select = quick_select_{};

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);

    let test = std::vector<int>{};

    let mt = std::mt19937{ std::random_device{}() };
    let rd = [&,dis = std::uniform_int_distribution{ -INF,INF }] mutable {
        return dis(mt);
    };

    for(let i in iota(0,1000)) {
        test.push_back(rd());
    }

    let constexpr find = 985;

    let it = quick_select(test.begin(),test.end(),find);
    std::cout << *it << '\n';
    std::ranges::sort(test);
    std::cout << test[find] << '\n';

    return 0;
}


