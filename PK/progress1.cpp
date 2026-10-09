

#include <bits/stdc++.h>

using i64 = long long;

using namespace std::views;
using namespace std::string_literals;
using namespace std::string_view_literals;
using std::ranges::to;
using std::ranges::subrange;

auto constexpr INF = std::numeric_limits<int>::max();
auto constexpr LNF = std::numeric_limits<i64>::max();
auto constexpr DNF = std::numeric_limits<double>::infinity();


struct scanner
{
    template<typename... T>
    auto operator()(T&&... args) const -> void
    {
        if constexpr(sizeof... (args) == 1) {
            using type = std::remove_cvref_t<std::tuple_element_t<0,std::tuple<T...>>>;
            if constexpr(requires {
                requires std::ranges::output_range<type, std::ranges::range_value_t<type>>;
                requires not std::same_as<std::remove_cvref_t<type>,std::string>;
            }) {
                std::ranges::for_each(std::forward<T>(args)..., *this);
            } else if constexpr(requires {
                typename std::tuple_size<std::remove_cvref_t<type>>::type;
            }) {
                std::apply(*this, std::forward<T>(args)...);
            } else {
                (std::cin >> ... >> args);
            }
        } else {
            ((*this)(args),...);
        }
    }
};

auto constexpr scan = scanner{};

auto constexpr dynamic_mod = 0;

template<typename T>
concept integer = std::integral<T> or std::same_as<T, __int128>;

template<integer auto MOD, typename MT = decltype(MOD)>
struct basic_mod
{
    auto constexpr static mod = MOD;
};

template<typename MT>
struct basic_mod<dynamic_mod, MT>
{
    MT mod;
};

template<integer T, integer auto MOD = dynamic_mod,integer MT = decltype(MOD)>
struct basic_mint : basic_mod<MOD, MT>
{
    using super = basic_mod<MOD, MT>;
    #define __M_DYNAMIC_MOD requires (MOD == dynamic_mod)
    #define __M_NOT_DYNAMIC_MOD requires (not (MOD == dynamic_mod))

    constexpr basic_mint() __M_NOT_DYNAMIC_MOD = default;

    constexpr basic_mint(T v) __M_NOT_DYNAMIC_MOD : val{v % this->mod}
    {
        norm<false>();
    }

    explicit constexpr basic_mint(MT mv) __M_DYNAMIC_MOD : super(mv) {}

    constexpr basic_mint(T v, MT mv) __M_DYNAMIC_MOD : super(mv), val(v % this->mod)
    {
        norm<false>();
    }

    auto constexpr norm() noexcept -> void
    {
        if(val >= this->mod) {
            val -= this->mod;
        } else if(val < 0) {
            val += this->mod;
        }
    }

    template<bool big>
    auto constexpr norm() noexcept -> void
    {
        if constexpr(big) {
            if(val >= this->mod) {
                val -= this->mod;
            }
        } else {
            if(val < 0) {
                val += this->mod;
            }
        }
    }

    [[nodiscard]]
    auto constexpr inv() const -> basic_mint
    {
        return pow(this->mod - 2);
    }

    [[nodiscard]]
    auto constexpr pow(integer auto p) const -> basic_mint
    {
        basic_mint v{ 1,this->mod }, mv{*this};
        for(; p; p >>= 1) {
            if(p & 1) {
                v *= mv;
            }
            mv *= mv;
        }
        return v;
    }

    auto constexpr operator^(integer auto p) const -> basic_mint { return pow(p); }

    constexpr explicit operator T() const noexcept
    {
        return val;
    }

    constexpr explicit operator bool() const noexcept
    {
        return bool(val);
    }

    auto constexpr operator-() const noexcept -> basic_mint
    {
        basic_mint ret;
        ret.val = this->mod - val;
        if constexpr(MOD == dynamic_mod) {
            ret.mod = this->mod;
        }
        return ret;
    }

    auto constexpr operator+=(basic_mint v) -> basic_mint &
    {
        val += v.val;
        norm<true>();
        return *this;
    }

    auto constexpr operator+=(std::integral auto v) -> basic_mint&
    {
        val += v;
        val %= this->mod;
        norm();
        return *this;
    }

    auto constexpr operator*=(basic_mint v) -> basic_mint &
    {

        val = static_cast<unsigned long long>(val) * v.val % this->mod;
        return *this;
    }

    auto constexpr operator*=(std::integral auto v) -> basic_mint&
    {
        if constexpr(std::signed_integral<decltype(v)>) {
            if(v < 0) {
                v %= this->mod;
                v += this->mod;
            }
        }
        val = static_cast<unsigned long long>(val) * v % this->mod;
        return *this;
    }

    auto constexpr operator-=(basic_mint v) -> basic_mint &
    {
        val -= v.val;
        norm<false>();
        return *this;
    }

    auto constexpr operator-=(std::integral auto v) -> basic_mint &
    {
        val -= v;
        norm();
        return *this;
    }

    auto constexpr operator/=(basic_mint v) -> basic_mint &
    {
        *this *= v.inv();
        return *this;
    }

    auto constexpr operator/=(std::integral auto v) -> basic_mint&
    {
        *this *= basic_mint{ v,this->mod }.inv();
        return *this;
    }

    auto friend constexpr operator+(basic_mint x, basic_mint y) -> basic_mint
    {
        x += y;
        return x;
    }
    auto friend constexpr operator+(basic_mint x, std::integral auto y) -> basic_mint
    {
        x += y;
        return x;
    }
    auto friend constexpr operator+(std::integral auto x, basic_mint y) -> basic_mint
    {
        y += x;
        return y;
    }

    auto friend constexpr operator*(basic_mint x, basic_mint y) -> basic_mint
    {
        x *= y;
        return x;
    }
    auto friend constexpr operator*(basic_mint x, std::integral auto y) -> basic_mint
    {
        x *= y;
        return x;
    }
    auto friend constexpr operator*(std::integral auto x, basic_mint y) -> basic_mint
    {
        y *= x;
        return y;
    }

    auto friend constexpr operator-(basic_mint x, basic_mint y) -> basic_mint
    {
        x -= y;
        return x;
    }
    auto friend constexpr operator-(basic_mint x, std::integral auto y) -> basic_mint
    {
        x -= y;
        return x;
    }
    auto friend constexpr operator-(std::integral auto x, basic_mint y) -> basic_mint
    {
        y -= x;
        y = -y;
        return y;
    }

    auto friend constexpr operator/(basic_mint x, basic_mint y) -> basic_mint
    {
        x /= y;
        return x;
    }
    auto friend constexpr operator/(basic_mint x, std::integral auto y) -> basic_mint
    {
        x /= y;
        return x;
    }
    auto friend constexpr operator/(std::integral auto x, basic_mint y) -> basic_mint
    {
        auto xx = basic_mint{ x,y.mod };
        xx /= y;
        return xx;
    }

    auto friend operator>>(auto &is, basic_mint &v) -> auto &
    {
        is >> v.val;
        v.val %= v.mod;
        v.norm();
        return is;
    }

    auto friend operator<<(auto &os, basic_mint v) -> auto & { return os << v.val; }

    auto friend constexpr operator==(basic_mint x, basic_mint y) -> bool { return x.val == y.val; }

    auto friend constexpr operator<=>(basic_mint x, basic_mint y)
    {
        return x.val <=> y.val;
    }

    T val;

    #undef __M_DYNAMIC_MOD
    #undef __M_NOT_DYNAMIC_MOD
};

using mint = basic_mint<i64>;

template<typename F>
struct make_transparent : F
{
    using F::operator();
    using is_transparent = void;
    constexpr explicit make_transparent(F&& f) : F(std::forward<F>(f)) {}
    constexpr make_transparent() = default;
};

template<std::integral T = int>
struct chtholly
{

    explicit chtholly(int n,T v = 0) : set({ std::make_pair(std::make_pair(0,n),v) }) {}

    template<typename R>
    explicit chtholly(R&& r)
    {
        auto lasti = 0,lastv = *r.begin();
        for(auto [i,v] : zip(iota(1),r | drop(1))) {
            if(v == lastv) {
                continue;
            }
            set.emplace(std::piecewise_construct,std::forward_as_tuple(lasti,i),std::forward_as_tuple(lastv));
            lasti = i;
            lastv = v;
        }
        set.emplace(std::piecewise_construct,std::forward_as_tuple(lasti,r.size()),std::forward_as_tuple(lastv));
    }

    auto split(int p)
    {
        auto it = set.lower_bound(p);
        auto [pv,v] = *it;
        auto [l,r] = pv;
        if(r == p) {
            return ++it;
        }
        set.erase(it);
        set.emplace(std::piecewise_construct,std::forward_as_tuple(l,p),std::forward_as_tuple(v));
        return std::get<0>(set.emplace(std::piecewise_construct,std::forward_as_tuple(p,r),std::forward_as_tuple(v)));
    }

    auto split(int l,int r)
    {
        auto ir = split(r),il = split(l);
        return std::make_pair(il,ir);
    }

    auto modify(int l,int r,std::integral auto v) -> void
    {
        " [l,r) 修改为 v "; // NOLINT
        auto [il,ir] = split(l,r);
        set.erase(il,ir);
        set.emplace(std::piecewise_construct,std::forward_as_tuple(l,r),std::forward_as_tuple(v));
    }

    auto add(int l,int r,std::integral auto v) -> void
    {
        " [l,r) 增加v "; // NOLINT
        auto [il,ir] = split(l,r);
        for(auto& val : subrange(il,ir) | values) {
            val += v;
        }
    }

    auto kth(int l,int r,int k) -> T
    {
        " [l,r) 第k小的数 (排序后第k个数) "; // NOLINT
        auto [il,ir] = split(l,r);
        auto a = subrange(il,ir) | transform([](auto const& p) {
            auto const& [pv,v] = p;
            auto [l,r] = pv;
            return std::make_pair(r - l,v);
        }) | to<std::vector>();
        std::ranges::sort(a,{},[](auto const& p) { return std::get<1>(p); });
        for(auto [cnt,v] : a) {
            if(k <= cnt) {
                return v;
            }
            k -= cnt;
        }
        " 一般调用者应该保证 k 不超出(r - l) "; // NOLINT
        return -1;
    }

    auto sump(int l,int r,int x,std::integral auto y) -> decltype(y)
    {
        " 范围[l,r)内的数 a^x mod y "; // NOLINT
        auto ans = mint{ decltype(y){},y };
        auto [il,ir] = split(l,r);
        for(auto const& [pv,v] : subrange(il,ir)) {
            auto [l,r] = pv;
            ans += (r - l) * (mint{ v,y }^x);
        }
        return ans.val;
    }

    using node = std::pair<int,int>;

    auto static constexpr cmp = make_transparent {
            []<typename CT,typename CU>(CT const& px,CU const& py) {
                auto constexpr fn = std::less{};
                if constexpr(std::same_as<CT,node>) {
                    if constexpr(std::same_as<CU,node>) {
                        return fn(std::get<1>(px),std::get<1>(py));
                    } else {
                        return fn(std::get<1>(px),py);
                    }
                } else {
                    return fn(px,std::get<1>(py));
                }
            }
    };
    std::map<node,T,decltype(cmp)> set;
};

template<typename R>
chtholly(R&& r) -> chtholly<std::ranges::range_value_t<R>>;

#define ONLINE_JUDGE

struct debugger
{
    template<typename... Args>
    auto static operator()(Args &&... args) -> void
    {
        #ifndef ONLINE_JUDGE
        ((std::cout << args << ' '),...);
        #endif
    }
    auto static operator()() -> void
    {
        #ifndef ONLINE_JUDGE
        std::cout << '\n';
        #endif
    }
};
auto constexpr debug = debugger{};

auto main1() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m,seed,vmax;
    scan(n,m,seed,vmax);
    auto sed = basic_mint<int,1000000007>{ seed };
    auto rnd = [&]() {
        return std::exchange(sed,sed * 7 + 13).val;
    };
    auto a = std::vector(n,0);
    for(auto& v : a) {
        v = rnd() % vmax + 1;
    }

    std::ranges::for_each(a,debug);
    debug();

    auto cht = chtholly<i64>{ a };
    for(auto i : iota(0,m)) {
        auto op = rnd() % 4 + 1;
        auto l = rnd() % n + 1;
        auto r = rnd() % n + 1;
        if(l > r) {
            std::swap(l,r);
        }
        auto x = op == 3 ? rnd() % (r - l + 1) : rnd() % vmax + 1;
        --l;
        if(op == 4) {
            auto y = rnd() % vmax + 1;
            debug(op,l,r,x,y);
            debug();
            std::println("{}",cht.sump(l,r,x,y));
        } else if(op == 1) {
            cht.add(l,r,x);
            debug(op,l,r,x);
            debug();
        } else if(op == 2) {
            cht.modify(l,r,x);
            debug(op,l,r,x);
            debug();
        } else {
            std::println("{}",cht.kth(l,r,x));
            debug(op,l,r,x);
            debug();
        }
    }


}
