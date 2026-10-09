


template<typename T = int,std::invocable<T,T> Exe = std::plus<T>>
struct fenwick
{

    template<std::integral I>
    explicit fenwick(I n,T init = {},Exe exe = {}) noexcept : a(std::vector<T>(n,init)),exe(exe){}

    fun modify(int i,T v) noexcept
    {
        for(; i <= a.size(); i += i & -i)
        {
            a[i - 1] = exe(a[i - 1],v);
        }
    }

    [[nodiscard]]
    fun query(int i) const noexcept -> T
    {
        T ret{};
        for(; i; i -= i & -i)
        {
            ret = exe(ret,a[i - 1]);
        }
        return ret;
    }

    [[nodiscard]]
    fun select(T k) const noexcept -> int = delete;

    std::vector<T> a;
    Exe exe;
};

template<typename T,typename Exe>
fun make_fenwick(std::integral auto n,Exe exe = {},T init = {}) -> fenwick<T,Exe>
{
return fenwick<T,Exe>{ n,exe,init };
}