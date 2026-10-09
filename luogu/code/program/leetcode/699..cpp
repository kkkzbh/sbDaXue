

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

using namespace std;

#define fun auto

template<typename V>
concept range_with_movable_references = std::ranges::input_range<V> &&
                                        std::move_constructible<std::ranges::range_reference_t<V>> &&
                                        std::move_constructible<std::ranges::range_rvalue_reference_t<V>>;

template<std::ranges::view V>
requires range_with_movable_references<V>
struct enumerate_view : public std::ranges::view_interface<enumerate_view<V>>
{
private:
    V range{};

    template<bool const_>
    struct iterator
    {
    private:
        friend enumerate_view;
        using base_ = std::conditional_t<const_,const V,V>;
        fun static s_iter_concept()
        {
            if constexpr (std::ranges::random_access_range<base_>)
            {
                return std::random_access_iterator_tag{};
            }
            else if constexpr (std::ranges::bidirectional_range<base_>)
            {
                return std::bidirectional_iterator_tag{};
            }
            else if constexpr (std::ranges::forward_range<base_>)
            {
                return std::forward_iterator_tag{};
            }
            else
            {
                return std::input_iterator_tag{};
            }
        }

    public:
        using iterator_category = std::input_iterator_tag;
        using iterator_concept = decltype(s_iter_concept());
        using difference_type = std::ranges::range_difference_t<base_>;
        using value_type = std::tuple<difference_type,std::ranges::range_value_t<base_>>;

    private:
        using reference_type = std::tuple<difference_type,std::ranges::range_value_t<base_>>;

        std::ranges::iterator_t<base_> it{};
        difference_type index_{};

        constexpr explicit iterator(std::ranges::iterator_t<base_> it,difference_type index_) : it(std::move(it)),index_(index_){}

    public:

        iterator() requires std::default_initializable<std::ranges::iterator_t<base_>> = default;

        constexpr iterator(iterator<!const_> i) requires const_ and std::convertible_to<std::ranges::iterator_t<V>,std::ranges::iterator_t<base_>>
                : it(std::move(i.it),index_(i.index_)){}

        fun constexpr base() const & noexcept  -> const std::ranges::iterator_t<base_> { return it; }

        fun constexpr base() && -> std::ranges::iterator_t<base_> { return std::move(it); }

        fun constexpr index() const noexcept -> difference_type { return index_; }

        fun constexpr operator*() const { return reference_type{ index_,*it }; }

        fun constexpr operator++() -> iterator&
        {
            ++it;
            ++index_;
            return *this;
        }

        fun constexpr operator++(int) -> void{ ++*this; }

        fun constexpr operator++(int)  -> iterator requires std::ranges::forward_range<base_>
        {
            auto tmp{ *this };
            ++*this;
            return tmp;
        }

        fun constexpr operator--() -> iterator& requires std::ranges::bidirectional_range<base_>
        {
            --it;
            --index_;
            return *this;
        }

        fun constexpr operator--(int) -> iterator requires std::ranges::bidirectional_range<base_>
        {
            auto tmp{ *this };
            --*this;
            return tmp;
        }

        fun constexpr operator+=(difference_type n) -> iterator& requires std::ranges::random_access_range<base_>
        {
            it += n;
            index_ += n;
            return *this;
        }

        fun constexpr operator-=(difference_type n) -> iterator& requires std::ranges::random_access_range<base_>
        {
            it -= n;
            index_ -= n;
            return *this;
        }

        fun constexpr operator[](difference_type i) const requires std::ranges::random_access_range<base_>
        { return reference_type{ index_ + i,it[i] }; }

        fun friend constexpr operator==(const iterator& x,const iterator& y) noexcept -> bool
        { return x.index_ == y.index_; }

        fun friend constexpr operator<=>(const iterator& x,const iterator& y) noexcept
        { return x.index_ <=> y.index_; }

        fun friend constexpr operator+(const iterator& x,difference_type y) -> iterator requires std::ranges::random_access_range<base_>
        {
            auto tmp{ x };
            tmp += y;
            return tmp;
        }

        fun friend constexpr operator-(const iterator& x,difference_type y) -> iterator requires std::ranges::random_access_range<base_>
        {
            auto tmp{ x };
            tmp -= y;
            return tmp;
        }

        fun friend constexpr operator-(const iterator& x,const iterator& y) -> difference_type
        { return x.it - y.it; }

        fun friend constexpr iter_move(const iterator& i) noexcept(noexcept(std::ranges::iter_move(i.it)) and std::is_nothrow_move_constructible_v<std::ranges::range_rvalue_reference_t<base_>>)
        {
            return std::tuple<difference_type,std::ranges::range_rvalue_reference_t<base_>>{ i.index_,std::ranges::iter_move(i.it) };
        }
    };

    template<bool const_>
    requires std::movable<std::ranges::range_value_t<V>>
    struct sentinel
    {
    private:
        using base_ = std::conditional_t<const_,const V,V>;

        std::ranges::sentinel_t<base_> it{};

        constexpr explicit sentinel(std::ranges::sentinel_t<base_> it) : it(std::move(it)){}

        friend enumerate_view;

    public:

        sentinel() = default;

        constexpr sentinel(sentinel<!const_> i) requires const_ and std::convertible_to<std::ranges::sentinel_t<V>,std::ranges::sentinel_t<base_>>
                : it(std::move(i.it)){}

        fun constexpr base() -> std::ranges::sentinel_t<base_> const { return it; }

        template<bool other_const>
        requires std::sentinel_for<std::ranges::sentinel_t<base_>,std::ranges::iterator_t<std::conditional_t<other_const,const V,V>>>
        fun friend constexpr operator==(const iterator<other_const>& x,const sentinel& y)
        { return x.it == y.it; }

        template<bool other_const>
        requires std::sized_sentinel_for<std::ranges::sentinel_t<base_>,std::ranges::iterator_t<std::conditional_t<other_const,const V,V>>>
        fun friend constexpr operator-(const iterator<other_const>& x,const sentinel& y) -> std::ranges::range_difference_t<std::conditional_t<other_const,const V,V>>
        { return x.it - y.it; };

        template<bool other_const>
        requires std::sized_sentinel_for<std::ranges::sentinel_t<base_>,std::ranges::iterator_t<std::conditional_t<other_const,const V,V>>>
        fun friend constexpr operator-(const sentinel& x,const iterator<other_const>& y) -> std::ranges::range_difference_t<std::conditional_t<other_const,const V,V>>
        { return x.it - y.it; };
    };

public:
    enumerate_view() requires std::default_initializable<V> = default;

    constexpr explicit enumerate_view(V base_) : range(std::move(base_)){}

    fun constexpr begin() requires (!(std::ranges::view<V> && std::ranges::range<const V> &&
                                      std::same_as<std::ranges::iterator_t<V>, std::ranges::iterator_t<const V>> &&
                                      std::same_as<std::ranges::sentinel_t<V>, std::ranges::sentinel_t<const V>>))
    { return iterator<false>{ std::ranges::begin(range),0 }; }

    fun constexpr begin() const requires range_with_movable_references<const V>
    { return iterator<true>{ std::ranges::begin(range),0 }; }

    fun constexpr end() requires (!(std::ranges::view<V> && std::ranges::range<const V> &&
                                    std::same_as<std::ranges::iterator_t<V>, std::ranges::iterator_t<const V>> &&
                                    std::same_as<std::ranges::sentinel_t<V>, std::ranges::sentinel_t<const V>>))
    {
        if constexpr(std::ranges::common_range<V> and std::ranges::sized_range<V>)
        {
            return iterator<false>{ std::ranges::end(range),std::ranges::distance(range) };
        }
        else
        {
            return sentinel<false>(std::ranges::end(range));
        }
    }

    fun constexpr end() const requires range_with_movable_references<const V>
    {
        if constexpr(std::ranges::common_range<const V> and std::ranges::sized_range<const V>)
        {
            return iterator<true>{ std::ranges::end(range),std::ranges::distance(range) };
        }
        else
        {
            return sentinel<true>(std::ranges::end(range));
        }
    }

    fun constexpr size() requires std::ranges::sized_range<V>
    { return std::ranges::size(range); }

    fun constexpr size() const requires std::ranges::sized_range<const V>
    { return std::ranges::size(range); }

    fun constexpr base() -> V const & requires std::copy_constructible<V>
    { return range; }

    fun constexpr base() && { return std::move(range); }

};

template<typename Range>
enumerate_view(Range&&) -> enumerate_view<std::views::all_t<Range>>;

template<typename T>
constexpr inline bool std::ranges::enable_borrowed_range<enumerate_view<T>> = std::ranges::enable_borrowed_range<T>;

template<typename T>
concept can_enumerate_views = requires { enumerate_view<std::views::all_t<T>>{ std::declval<T>() }; };

struct enumerate_
{
    template<typename Self,typename Range>
    requires std::invocable<Self,Range>
    fun friend constexpr operator|(Range&& r,Self&& self)
    { return std::forward<Self>(self)(std::forward<Range>(r)); }

    template<std::ranges::viewable_range Range>
    requires can_enumerate_views<Range>
    fun constexpr operator() [[nodiscard]] (Range&& r) const
    { return enumerate_view<std::views::all_t<Range>>(std::forward<Range>(r)); }
};

constexpr inline enumerate_ enumerate;

template<typename T = int,typename Ret = T>
struct xds
{
    template<std::integral I>
    explicit xds(I n) noexcept : a(std::vector<T>(n << 2)),lazy_(std::vector<std::optional<T>>(n << 2)){}

    template<std::random_access_iterator It,typename Se>
    requires requires(It it) { { *it } -> std::convertible_to<T>; } and std::sentinel_for<Se,It>
    xds(It first_,Se end_) noexcept
    {
        int n{ static_cast<int>(std::distance(first_,end_)) };
        a.resize(n << 2);
        lazy_.resize(n << 2);
        build(0,n - 1,0,first_);
    }

    template<std::ranges::range Range>
    explicit xds(Range&& r) noexcept : xds(std::ranges::begin(r),std::ranges::end(r)) {}

    [[nodiscard]]
    fun query(int l,int r) noexcept -> Ret
    {
        return query(0,(a.size() >> 2) - 1,0,l,r);
    }

    fun modify(int l,int r,T v) noexcept -> void
    {
        modify(0,(a.size() >> 2) - 1,0,l,r,query(l,r) + v);
    }

    fun size() const noexcept -> int
    {
        return a.size() >> 2;
    }

private:

    fun modify(int l,int r,int i,int lt,int rt,T v) -> void
    {
        if(lt <= l and r <= rt) {
            a[i] = v;
            lazy_[i] = a[i];
        } else {
            int mid{ (l + r) >> 1 };
            update(i);
            if(lt <= mid) {
                modify(l,mid,left(i),lt,rt,v);
            }
            if(rt > mid) {
                modify(mid + 1,r,right(i),lt,rt,v);
            }
            merge(i);
        }
    }

    fun query(int l,int r,int i,int lt,int rt) noexcept -> Ret
    {
        if(lt <= l and r <= rt) {
            return a[i];
        }
        int mid{ (l + r) >> 1 };
        update(i);
        Ret ret{};
        if(lt <= mid) {
            ret = std::max(ret,query(l,mid,left(i),lt,rt));
        }
        if(rt > mid) {
            ret = std::max(ret,query(mid + 1,r,right(i),lt,rt));
        }
        return ret;
    }

    fun update(int i) noexcept -> void
    {
        if(lazy_[i]) {
            int lt{ left(i) },rt{ right(i) };
            lazy_[lt] = lazy_[i];
            lazy_[rt] = lazy_[i];
            a[lt] = a[rt] = *lazy_[i];
            lazy_[i] = {};
        }
    }

    fun merge(int i) noexcept -> void
    {
        a[i] = std::max(a[left(i)],a[right(i)]);
    }

    template<std::random_access_iterator It>
    fun build(int l,int r,int i,It first_) noexcept -> void
    {
        if(l == r) {
            a[i] = first_[l];
        } else {
            int mid{ (l + r) >> 1 };
            build(l,mid,left(i),first_);
            build(mid + 1,r,right(i),first_);
            merge(i);
        }
    }

    fun static constexpr left(int i) noexcept -> int { return (i << 1) | 1; }
    fun static constexpr right(int i) noexcept -> int { return left(i) + 1; }

    std::vector<T> a;
    std::vector<std::optional<T>> lazy_;
};



class Solution {
public:
    std::vector<int> fallingSquares(std::vector<std::vector<int>>& positions)
    {
        std::vector<int> dis;
        for(const auto& [i,len] : positions | views::transform([](auto& v){ return std::tie(v[0],v[1]); })) {
            dis.push_back(i);
            dis.push_back(i + len - 1);
        }
        std::ranges::sort(dis);
        auto ur{ std::ranges::unique(dis) };
        dis.erase(ur.begin(),ur.end());
        std::unordered_map<int,int> map;
        for(auto [i,v] : dis | enumerate) {
            map[v] = i;
        }
        xds fw{ dis.size() };
        std::vector<int> ret;
        for(const auto& [i,len] : positions | views::transform([](auto& v){ return std::tie(v[0],v[1]); })){
            fw.modify(map[i],map[i + len - 1],len);
            ret.push_back(fw.query(0,fw.size() - 1));
        }
        return ret;
    }
};
