


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