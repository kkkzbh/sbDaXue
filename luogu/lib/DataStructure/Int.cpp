struct Int
{

    using base_t = int;

    Int() : a(1,0) {}

    Int(std::integral auto val)
    {
        for(; val; val /= 10) {
            a.push_back(val % 10);
        }
    }

    Int(const std::string& s)
    {
        for(char c : s | reverse) {
            a.push_back(c ^ 48);
        }
    }

    Int(const Int& v) : a{ v.a } {}

    Int(Int&& v) : a{ std::move(v.a) } {}

    fun operator=(const Int& v) -> Int& = default;

    fun operator=(Int&& v) -> Int& = default;

    [[nodiscard]]
    fun bit() const noexcept -> int
    { return static_cast<int>(a.size()); }

    fun operator[](int i) noexcept -> base_t&
    { return a[i]; }

    fun operator[](int i) const noexcept -> base_t
    { return a[i]; }

    fun operator+=(const Int& v) -> Int&
    {
        int mbit = std::max(bit(),v.bit());
        a.resize(mbit + 1);
        for(int i : iota(0,v.bit())) {
            a[i] += v[i];
        }
        for(int i : iota(0,bit() - 1)) {
            if(a[i] >= 10) {
                a[i + 1] += 1;
                a[i] -= 10;
            }
        }
        if(!a.back()) { // 优化首0
            a.resize(a.size() - 1);
        }
        return *this;
    }

    fun operator+=(std::integral auto I) -> Int&
    {
        a[0] += I;
        for(int i{}; a[i] >= 10; ++i) {
            if(bit() <= i + 1) {
                a.resize(i + 2);
            }
            a[i + 1] += a[i] % 10;
            a[i] /= 10;
        }
    }

    fun operator-=(const Int& v) -> Int& // 目前不支持负数
    {
        for(int i : iota(0,v.bit())) {
            a[i] -= v[i];
        }
        for(int i : iota(0,bit())) {
            if(a[i] < 0) {
                --a[i + 1];
                a[i] += 10;
            }
        }
        int n = bit();
        for(--n; !a[n]; --n){}
        a.resize(n + 1);
        return *this;
    }

    fun friend operator-(const Int& x,const Int& y) -> Int
    {
        Int res{ x };
        res -= y;
        return res;
    }

    fun friend operator*(const Int& x,const Int& y) -> Int
    {
        Int res(std::vector<base_t>(x.bit() + y.bit(),0));
        for(int i : iota(0,x.bit())) {
            for(int j : iota(0,y.bit())) {
                res[i + j] += x[i] * y[j];
            }
        }
        for(int i : iota(0,res.bit() - 1)) {
            res[i + 1] += res[i] / 10;
            res[i] %= 10;
        }
        if(!res.a.back()) {
            res.a.resize(res.bit() - 1);
        }
        return res;
    }


    fun operator*=(const Int& v) -> Int&
    { return *this = *this * v; }

    fun friend operator+(const Int& x,const Int& y)
    {
        Int res{ x };
        res += y;
        return res;
    }

    fun friend operator+(Int v,std::integral auto I) -> Int
    {
        v += I;
        return v;
    }

    fun friend operator<<(auto& os,const Int& v) -> auto&
    {
        for(base_t val : v.a | reverse) {
            os << val;
        }
        return os;
    }

private:
    std::vector<base_t > a;

    explicit Int(std::vector<base_t>&& v) : a{ std::move(v) } {}
};

fun pow(Int v,std::integral auto I) -> Int
{
Int ret{ 1 };
for(; I; v *= v,I >>= 1) {
if(I & 1) {
ret *= v;
}
}
return ret;
}