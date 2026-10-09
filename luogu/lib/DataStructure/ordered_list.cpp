template<typename T,std::invocable<T,T> Cmp = std::less<>>
requires requires(T v,Cmp c) {
{ c(v,v) } -> std::convertible_to<bool>;
}
struct ordered_list
{
    using value_type = T;
    struct node : std::pair<value_type,int>
    {
        using base_type = std::pair<value_type,int>;
        using base_type::base_type;

        template<typename U>
        node(U&& val) : base_type{ std::forward<U>(val),0 } // NOLINT
        {}
    };
    struct pair_cmp
    {
        pair_cmp() requires std::default_initializable<Cmp> = default;

        explicit pair_cmp(Cmp&& cmp) : cmp{ std::move(cmp) } {}

        fun operator()(node const& n1,node const& n2) -> bool
        { return cmp(n1.first,n2.first); }

        Cmp cmp;
    };
    using timestamp =               std::pair<value_type const&,int>;
    using container =               __gnu_pbds::tree<node,__gnu_pbds::null_type,pair_cmp,__gnu_pbds::rb_tree_tag,__gnu_pbds::null_node_update>;
    using iterator =                container::iterator;
    using const_iterator =          container::const_iterator;
    using reverse_iterator =        container::reverse_iterator;
    using const_reverse_iterator =  container::const_reverse_iterator;
    using compare =                 Cmp;
    using reference =               value_type&;
    using const_reference =         value_type const&;

    ordered_list() requires std::default_initializable<Cmp> = default;

    ordered_list(ordered_list const& other) = default;

    explicit ordered_list(Cmp cmp) : a{ pair_cmp{ std::move(cmp) } } {}

    template<std::input_iterator It,std::sentinel_for<It> St>
    ordered_list(It first,St last,Cmp cmp = {}) requires std::default_initializable<Cmp> : a{ std::move(first),std::move(last),pair_cmp{ std::move(cmp) } }
    {}

    template<std::ranges::input_range R>
    explicit ordered_list(R&& r,Cmp cmp = {}) requires std::default_initializable<Cmp> : ordered_list(std::ranges::begin(r),std::ranges::end(r),cmp) {};

    fun begin() -> iterator
    { return a.begin(); }

    fun end() -> iterator
    { return a.end(); }

    fun rbegin() -> reverse_iterator
    { return a.rbegin(); }

    fun rend() -> reverse_iterator
    { return a.rend(); }

    [[nodiscard]]
    fun empty() const -> bool
    { return a.empty(); }

    [[nodiscard]]
    fun size() const -> auto
    { return a.size(); }

    fun lower_bound(value_type const& val) -> iterator
    { return a.lower_bound(timestamp{ val,0 }); }

    template<typename... Args>
    fun emplace(Args&&... args) -> iterator
    {
        let val = value_type{ std::forward<Args>(args)... };
        insert(std::move(val));
    }

    fun insert(value_type const& val) -> iterator
    {
        let [it,flag] = a.insert(node{ val,0 });
        const_cast<int&>(it->second) += flag ^ 1;
        return it;
    }

    fun insert(value_type&& val) -> iterator
    {
        let [it,flag] = a.insert(node{ std::move(val),0 });
        const_cast<int&>(it->second) += flag ^ 1;
        return it;
    }

    fun erase(value_type const& val) -> bool
    { return erase(find(val)); }

    fun erase(iterator it) -> bool
    {
        if(it == end()) {
            return false;
        }
        if(not const_cast<int&>(it->second)--) {
            a.erase(it);
        }
        return true;
    }

    fun erase(reverse_iterator it) -> bool
    {
        if(it == rend()) {
            return false;
        }
        if(not const_cast<int&>(it->second)--) {
            a.erase(it);
        }
        return true;
    }

    [[nodiscard]]
    fun front() -> value_type const&
    { return begin()->first; }

    [[nodiscard]]
    fun back() -> value_type const&
    { return rbegin()->first; }

    fun pop_front() -> void
    { erase(begin()); }

    fun pop_back() -> void
    { erase(rbegin()); }

    fun del(value_type const& val) -> bool
    { return a.erase(find(val)); }

    fun del(iterator it) -> bool
    { return a.erase(it); }

    fun del(reverse_iterator it) -> bool
    { return a.erase(it); }

    fun find(value_type const& val) -> iterator
    { return a.find(node{ val,{} }); }

    fun contains(value_type const& val) -> bool
    { return find(val) != end(); }

    container a;
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
explicit ordered_list(Cmp cmp) -> ordered_list<typename function_traits<decltype(std::function{ cmp })>::template argument_type<0>,std::less<>>;

template<typename It,typename St,typename Cmp = std::less<>>
explicit ordered_list(It first,St last,Cmp cmp = {}) -> ordered_list<typename std::decay_t<It>::value_type,std::less<>>;

template<typename R,typename Cmp = std::less<>>
explicit ordered_list(R&& r,Cmp cmp = {}) -> ordered_list<typename std::decay_t<R>::value_type,std::less<>>;
