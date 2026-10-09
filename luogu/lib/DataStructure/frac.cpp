template<typename Tn,typename Td = Tn>
requires (std::integral<Tn> or std::same_as<Tn,__int128>) and (std::integral<Td> or std::same_as<Td,__int128>)
struct frac
{

    constexpr frac(Tn num,Td den) noexcept : num(num),den(den)
    {
        if(den < 0)
        {
            this->den = -den;
            this->num = -num;
        }
    }

    constexpr frac(Tn num) noexcept : num(num),den(1){}

    constexpr frac() noexcept requires std::default_initializable<Tn> and std::default_initializable<Td> = default;

    explicit constexpr operator double() const noexcept
    {
        return static_cast<double>(num) / den;
    }

    explicit constexpr operator bool() const noexcept
    { return num; }

    [[nodiscard]]
    fun constexpr floor() const noexcept -> std::common_type_t<Tn,Td>
    {
        return num % den ? (num / den) - (num > 0 != den > 0) : num / den;
    }

    [[nodiscard]]
    fun constexpr ceil() const noexcept -> std::common_type_t<Tn,Td>
    {
        return num % den ? (num / den) + (num > 0 == den > 0) : num / den;
    }

    fun constexpr reduce() noexcept -> frac&
    {
        Tn g{ std::gcd(num,den) };
        num /= g;
        den /= g;
        return *this;
    }

    fun constexpr operator+=(const frac& n) noexcept -> frac&
    {
        num = num * n.den + n.num * den;
        den *= n.den;
        return *this;
    }

    fun constexpr operator-=(const frac& n) noexcept -> frac&
    {
        num = num * n.den - n.num * den;
        den *= n.den;
        return *this;
    }

    fun constexpr operator*=(const frac& n) noexcept -> frac&
    {
        num *= n.num;
        den *= n.den;
        return *this;
    }

    fun constexpr operator/=(const frac& n) noexcept -> frac&
    {
        num *= n.den;
        den *= n.num;
        if(den < 0)
        {
            num = -num;
            den = -den;
        }
        return *this;
    }

    fun constexpr friend operator+(frac x,const frac& y) noexcept -> frac
    {
        x += y;
        return x;
    }

    fun constexpr friend operator-(frac x,const frac& y) noexcept -> frac
    {
        x -= y;
        return x;
    }

    fun constexpr friend operator*(frac x,const frac& y) noexcept  -> frac
    {
        x *= y;
        return x;
    }

    fun constexpr friend operator/(frac x,const frac& y) noexcept  -> frac
    {
        x /= y;
        return x;
    }

    fun constexpr friend operator-(frac x) noexcept -> frac
    {
        x.num = -x.num;
        return x;
    }

    fun constexpr friend operator==(const frac& x,const frac& y) noexcept -> bool
    {
        return x.num * y.den == y.num * x.den;
    }

    fun constexpr friend operator<=>(const frac& x,const frac& y) noexcept -> std::strong_ordering
    {
        return x.num * y.den <=> y.num * x.den;
    }

    fun friend operator<<(std::ostream& os,const frac& n) noexcept -> std::ostream&
    {
        Tn g{ std::gcd(n.num,n.den) };
        if(n.den == g)
        {
            return os << n.num / g;
        }
        else
        {
            return os << n.num / g << '/' << n.den / g;
        }
    }

    Tn num{};
    Td den{ 1 };

};

template<typename T>
requires std::is_integral_v<T>
frac(T) -> frac<T>;

namespace std
{
    template<typename Tn,typename Td>
    auto abs(frac<Tn,Td> const& f) -> frac<Tn,Td>
{
    if(f < 0) {
    return -f;
}
return f;
}
}