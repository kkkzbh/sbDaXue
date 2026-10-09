

#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

#define let auto
#define fun auto
#define in :




template<typename T,typename M_cmp = decltype([](const T& a,const T& b){ return a < b; })>
struct avl
{
    constexpr static int null{};

    struct node
    {
        T val{};
        int left{ null };
        int right{ null };
        int sz{ 1 };
        int hei{ 1 };
        int cnt{ 1 };
        node() requires std::default_initializable<T> = default;
        node(const T& v) : val(v){}
    };

    std::vector<node> a{ { T{},null,null,0,0,0 } };
    int root{ null };
    int M_tp{ 1 };
    std::vector<int> del;

    fun operator[](int index) -> T&
    {
        return a[index].val;
    }

    void insert(const T& val)
    {
        M_insert(root,val);
    }

    void erase(const T& val)
    {
        M_erase(root,val);
    }

    void inorder()
    {
        M_inorder(root);
    }

    T find_kth(int k)
    {
        int it{ root };
        while(it != null)
        {
            if(a[a[it].left].sz + a[it].cnt < k)
            {
                k -= a[a[it].left].sz + a[it].cnt;
                it = a[it].right;
            }
            else if(a[a[it].left].sz >= k )
                it = a[it].left;
            else
                return a[it].val;
        }
    }

    int val_kth(const T& val) const
    {
        int rt{ root };
        int ret{};
        while(rt != null)
        {
            if(M_cmp{}(val,a[rt].val))
            {
                rt = a[rt].left;
            }
            else if(M_cmp{}(a[rt].val,val))
            {
                ret += a[a[rt].left].sz + a[rt].cnt;
                rt = a[rt].right;
            }
            else
            {
                ret += a[a[rt].left].sz;
                rt = null;
            }
        }
        return ret + 1;
    }

private:

    void M_inorder(const int it)
    {
        if(it == null)
            return;
        M_inorder(a[it].left);
        std::cout << a[it].val << ' ';
        M_inorder(a[it].right);
    }

    void M_insert(int& it,const T& val)
    {
        if(it == null)
        {
            if(del.empty())
                a[it = M_tp++].val = val;
            else
            {
                a[it = del.back()].val = val;
                del.pop_back();
            }
            return;
        }

        if(a[it].val == val)
        {
            ++a[it].cnt;
            ++a[it].sz;
            return;
        }

        if(M_cmp{}(val,a[it].val))
            M_insert(a[it].left,val);
        else
            M_insert(a[it].right,val);

        int rt{ it };

        rotation(it);

        a[rt].hei = heigh(rt);
        a[rt].sz = size(rt);
    }

    void M_erase(int& it,const T& val)
    {
        if(it == null)
            return;
        if(M_cmp{}(val,a[it].val))
        {
            M_erase(a[it].left,val);
        }
        else if(M_cmp{}(a[it].val,val))
        {
            M_erase(a[it].right,val);
        }
        else
        {
            if(a[it].left != null && a[it].right != null)
            {
                if(a[it].cnt == 1)
                {
                    int rt{a[it].right};
                    while (a[rt].left != null)
                        rt = a[rt].left;
                    std::swap(a[it].val, a[rt].val);
                    std::swap(a[it].cnt, a[rt].cnt);
                    M_erase(a[it].right, val);
                }
                else
                {
                    --a[it].cnt;
                    --a[it].sz;
                    return;
                }
            }
            else if(a[it].left != null)
            {
                if(a[it].cnt == 1)
                {
                    int rt{ a[it].left };
                    del.push_back(it);
                    a[it].left = a[it].right = null;
                    a[it].hei = a[it].sz = 1;
                    it = rt;
                }
                else
                {
                    --a[it].cnt;
                    --a[it].sz;
                }
                return;
            }
            else
            {
                if(a[it].cnt == 1)
                {
                    int rt{ a[it].right };
                    del.push_back(it);
                    a[it].left = a[it].right = null;
                    a[it].hei = a[it].sz = 1;
                    it = rt;
                }
                else
                {
                    --a[it].cnt;
                    --a[it].sz;
                }
                return;
            }
        }

        int rt{ it };

        rotation(it);

        a[rt].hei = heigh(rt);
        a[rt].sz = size(rt);
    }

    void rotation(int& it)
    {
        int bf{ a[a[it].left].hei - a[a[it].right].hei };
        if(bf == -2)    //右
        {
            if(a[a[a[it].right].left].hei <= a[a[a[it].right].right].hei) //右
            {
                leftrotation(it);
            }
            else    //左
            {
                rightrotation(a[it].right);
                a[a[a[it].right].right].hei = heigh(a[a[it].right].right);
                leftrotation(it);
            }
        }
        else if(bf == 2)    //左
        {
            if(a[a[a[it].left].left].hei < a[a[a[it].left].right].hei)  //右
            {
                leftrotation(a[it].left);
                a[a[a[it].left].left].hei = heigh(a[a[it].left].left);
                rightrotation(it);
            }
            else    //左
            {
                rightrotation(it);
            }
        }
    }

    int heigh(int it)
    {
        return std::max(a[a[it].left].hei,a[a[it].right].hei) + 1;
    }

    int size(int it)
    {
        return a[a[it].left].sz + a[a[it].right].sz + a[it].cnt;
    }

    void leftrotation(int& it)  //左旋
    {
        int r{ a[it].right };
        a[it].right = a[r].left;
        a[r].left = it;
        a[it].sz = size(it);
        a[r].sz = size(r);
        it = r;
    }

    void rightrotation(int& it)
    {
        int l{ a[it].left };
        a[it].left = a[l].right;
        a[l].right = it;
        a[it].sz = size(it);
        a[l].sz = size(l);
        it = l;
    }
};

using namespace std;

#define UPBDS(X) using __gnu_pbds::X;
UPBDS(tree) UPBDS(null_type) UPBDS(rb_tree_tag) UPBDS(null_node_update)

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

class Solution {
public:
    int static minimumDeviation(vector<int>& a)
    {
        for(let &v in a | views::filter([&](int v){ return v & 1; })) {
            v *= 2;
        }
        let l = ordered_list{ a };

        let ans = l.back() - l.front();

        while(not (l.back() & 1)) {
            let v = l.back();
            l.pop_back();
            v /= 2;
            l.insert(v);
            ans = std::min(ans,l.back() - l.front());
        }
        return ans;

    }
};