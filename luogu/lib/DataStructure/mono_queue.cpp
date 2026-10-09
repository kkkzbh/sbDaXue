template<typename T,typename Cmp = std::less<>,typename Proj = std::identity>
requires std::invocable<Proj,T> and
         std::invocable<Cmp,std::invoke_result_t<Proj,T>,std::invoke_result_t<Proj,T>> and
std::convertible_to<std::invoke_result_t<Cmp,std::invoke_result_t<Proj,T>,std::invoke_result_t<Proj,T>>,bool>
struct mono_queue
{
    fun push(T v) noexcept
    {
        while(!que.empty() and cmp(proj(v),proj(que.back()))) {
            que.pop_back();
        }
        que.push_back(v);
    }

    fun pop(T v) noexcept
    {
        if(que.front() == v) {
            que.pop_front();
        }
    }

    [[nodiscard]]
    fun top() const noexcept
    {
        return proj(que.front());
    }

    [[nodiscard]]
    fun operator*() const noexcept
    {
        return top();
    }

    [[nodiscard]]
    fun empty() const noexcept -> bool
    {
        return que.empty();
    }

    [[nodiscard]]
    fun clear() noexcept
    {
        que.clear();
    }

    mono_queue() noexcept requires std::default_initializable<Cmp> and std::default_initializable<Proj> = default;

    explicit mono_queue(Cmp c) noexcept requires std::default_initializable<Proj> : mono_queue(c,{}) {}

    explicit mono_queue(Proj p) noexcept requires std::default_initializable<Cmp> : mono_queue({},p) {}

    mono_queue (Cmp c,Proj p) noexcept : cmp(c),proj(p){}

    Cmp cmp;
    Proj proj;

    std::deque<T> que;
};

template<typename T,typename Cmp,typename Proj>
fun make_mono_queue(Cmp cmp = {},Proj proj = {}) -> mono_queue<T,Cmp,Proj>
{
return mono_queue<T,Cmp,Proj>{ cmp,proj };
}