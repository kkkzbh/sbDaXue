

template<typename T,int MOD_>
struct carray
{
    auto begin() noexcept
    {
        return std::ranges::begin(a);
    }

    auto end() noexcept
    {
        return std::ranges::end(a);
    }

    auto operator[](int i) noexcept
    {
        return a[i > MOD_ ? i % MOD_ : i];
    }
    T a[MOD_]{};
};

