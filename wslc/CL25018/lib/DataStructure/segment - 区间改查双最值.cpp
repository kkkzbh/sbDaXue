template<typename T>
struct segment
{
    template<std::integral I>
    explicit segment(I n) noexcept : a(decltype(a)(n << 2)),b(decltype(b)(n << 2)),lazy(decltype(lazy)(n << 2)){}

    template<std::random_access_iterator It,typename Se>
    requires requires(It it) { { *it } -> std::convertible_to<T>; } and std::sentinel_for<Se,It>
    segment(It first_,Se end_) noexcept : segment(std::distance(first_,end_))
    { build(0,std::distance(first_,end_) - 1,0,first_); }

    template<std::ranges::random_access_range Range>
    explicit segment(Range&& r) noexcept : segment(std::ranges::begin(r),std::ranges::end(r)) {}

    [[nodiscard]]
    auto max(int l,int r) noexcept -> T
    {
        return max(0,size() - 1,0,l,r);
    }

    [[nodiscard]]
    auto min(int l,int r) noexcept -> T
    {
        return min(0,size() - 1,0,l,r);
    }

    auto modify(int l,int r,T v) noexcept -> void
    {
        modify(0,size() - 1,0,l,r,v);
    }

    [[nodiscard]]
    auto size() const noexcept -> int
    {
        return a.size() >> 2;
    }

private:

    auto modify(int l,int r,int i,int lt,int rt,T v) -> void
    {
        if(lt <= l and r <= rt) {
            lazy[i] = v;
            a[i] = v;
            b[i] = v;
        } else {
            int mid{ (l + r) >> 1 };
            update(i,mid - l + 1,r - mid);
            if(lt <= mid) {
                modify(l,mid,left(i),lt,rt,v);
            }
            if(rt > mid) {
                modify(mid + 1,r,right(i),lt,rt,v);
            }
            merge(i);
        }
    }

    auto max(int l,int r,int i,int lt,int rt) noexcept -> T
    {
        if(lt <= l and r <= rt) {
            return a[i];
        }
        int mid{ (l + r) >> 1 };
        update(i,mid - l + 1,r - mid);
        T ret{ std::numeric_limits<T>::min() };
        if(lt <= mid) {
            ret = std::max(max(l,mid,left(i),lt,rt),ret);
        }
        if(rt > mid) {
            ret = std::max(max(mid + 1,r,right(i),lt,rt),ret);
        }
        return ret;
    }

    auto min(int l,int r,int i,int lt,int rt) noexcept -> T
    {
        if(lt <= l and r <= rt) {
            return b[i];
        }
        int mid{ (l + r) >> 1 };
        update(i,mid - l + 1,r - mid);
        T ret{ std::numeric_limits<T>::max() };
        if(lt <= mid) {
            ret = std::min(min(l,mid,left(i),lt,rt),ret);
        }
        if(rt > mid) {
            ret = std::min(min(mid + 1,r,right(i),lt,rt),ret);
        }
        return ret;
    }

    auto update(int i,int ln,int rn) noexcept -> void
    {
        if(lazy[i]) {
            int lt{ left(i) },rt{ right(i) };
            lazy[lt] = lazy[i];
            lazy[rt] = lazy[i];
            a[lt] = *lazy[i];
            b[lt] = *lazy[i];
            a[rt] = *lazy[i];
            b[rt] = *lazy[i];
            lazy[i] = {};
        }
    }

    auto merge(int i) noexcept -> void
    {
        a[i] = std::max(a[left(i)],a[right(i)]);
        b[i] = std::min(b[left(i)],b[right(i)]);
    }

    template<std::random_access_iterator It>
    auto build(int l,int r,int i,It first_) noexcept -> void
    {
        if(l == r) {
            a[i] = first_[l];
            b[i] = first_[r];
        } else {
            int mid{ (l + r) >> 1 };
            build(l,mid,left(i),first_);
            build(mid + 1,r,right(i),first_);
            merge(i);
        }
    }

    auto static constexpr left(int i) noexcept -> int { return (i << 1) | 1; }
    auto static constexpr right(int i) noexcept -> int { return left(i) + 1; }

    std::vector<T> a,b;
    std::vector<std::optional<T>> lazy;
};

template<std::random_access_iterator It,typename Se>
segment(It first_,Se end_) -> segment<typename std::iterator_traits<It>::value_type>;

template<std::ranges::random_access_range Range>
segment(Range&& r) -> segment<std::ranges::range_value_t<Range>>;