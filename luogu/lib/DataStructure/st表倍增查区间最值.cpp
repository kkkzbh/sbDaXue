
template<typename T = int,typename Exe = decltype(std::ranges::max),typename Proj = std::identity>
requires std::invocable<Exe,std::invoke_result_t<Proj,T>,std::invoke_result_t<Proj,T>>
struct st
{
    template<std::input_iterator It,std::sentinel_for<It> Se>
    st(It first_,Se end_,Exe exe = {},Proj proj = {}) requires std::convertible_to<std::iter_value_t<It>,T> : a(),exe(exe),proj(proj)
    {
        a.emplace_back();
        while(first_ != end_) {
            a[0].push_back(*first_++);
        }
        int lg = lg2[a[0].size()];
        a.resize(lg + 1);
        for(int p{ 1 }; p <= lg; ++p) {
            a[p].resize(a[0].size());
            for(int i{},off{ 1 << (p - 1) }; i + off < a[p].size(); ++i) {
                a[p][i] = exe(proj(a[p - 1][i]),proj(a[p - 1][i + (1 << (p - 1))]));
            }
        }
    }

    template<std::input_iterator It>
    st(It first_,int n,Exe exe = {},Proj proj = {}) requires std::convertible_to<std::iter_value_t<It>,T> : a(),exe(exe),proj(proj)
    {
        a.emplace_back();
        while(n) {
            a[0].push_back(*first_);
            if(--n) {
                ++first_;
            }
        }
        int lg = lg2[a[0].size()];
        a.resize(lg + 1);
        for(int p{ 1 }; p <= lg; ++p) {
            a[p].resize(a[0].size());
            for(int i{},off{ 1 << (p - 1) }; i + off < a[p].size(); ++i) {
                a[p][i] = exe(proj(a[p - 1][i]),proj(a[p - 1][i + (1 << (p - 1))]));
            }
        }
    }

    template<std::ranges::input_range R>
    explicit st(R&& r,Exe exe = {},Proj proj = {}) : st(std::ranges::begin(r),std::ranges::end(r),exe,proj){}

    [[nodiscard]]
    T reduce(int l,int r) const noexcept
    {
        int lg{ lg2[r - l + 1] };
        return exe(proj(a[lg][l]),proj(a[lg][r - (1 << lg) + 1]));
    }

    T operator()(int l,int r) const noexcept
    { return reduce(l,r); }

private :

    constexpr static int lg2cei = 104857;

    constexpr static std::array<int,lg2cei> lg2 = []() consteval {
        std::array<int,lg2cei> ret{};
        for(int i{ 2 }; i != ret.size(); ++i) {
            ret[i] = ret[i / 2] + 1;
        }
        return ret;
    }();

    std::vector<std::vector<T>> a;
    Exe exe;
    Proj proj;
};