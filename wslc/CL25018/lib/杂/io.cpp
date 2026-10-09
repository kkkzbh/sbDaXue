
template<typename T>
concept STD_array = requires(T array)
{
    typename T::value_type;
    { array[0] } -> std::same_as<std::add_lvalue_reference<typename T::value_type>>;
};

template<typename T>
concept Array = STD_array<T> or std::is_array_v<T>;

template<typename... Args>
auto print(const std::format_string<Args...> fmts,Args&&... args)
{ std::cout << std::vformat(fmts.get(), std::make_format_args(args...)); }

template<typename F,typename... T>
auto print(F&& farg,T&&... args)
{
    std::cout << farg;
    ((std::cout << ' ' << args), ...);
}

template<typename... Args>
auto println(const std::format_string<Args...> fmts,Args&&... args)
{
    print(fmts,std::forward<Args>(args)...);
    println();
}

template<typename...T>
auto println(T&&... args)
{
    if constexpr(not sizeof...(args)) {
        std::cout << '\n';
    } else {
        ((std::cout << args << '\n'), ...);
    }
}

template<Array T>
auto scan(T& array,int n)
{
    if constexpr(std::is_array_v<T>)
    {
        std::copy_n(std::istream_iterator<std::remove_all_extents_t<T>>{ std::cin },n, std::ranges::begin(array) + 1);
    }
    else
    {
        std::copy_n(std::istream_iterator<typename T::value_type>{ std::cin },n,array.begin() + 1);
    }
}

template<Array T,std::integral... Args>
auto scan(T& array,int n,Args... args)
{
    for(int i : iota(1,n + 1))
    {
        scan(array[i],args...);
    }
}

template<typename... Args>
auto scan(Args&... args)
{
    (std::cin >> ... >> args);
}

namespace fasti
{
    struct istream
    {
        template<typename T>
        struct iterator
        {
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            auto friend operator==(iterator x,iterator y) { return !normal; }
            auto operator++() -> iterator&
            {
                if(lazy) {
                    cin >> val;
                } else {
                    lazy = true;
                }
                return *this;
            }
            auto operator++(int) -> iterator
            {
                iterator ret{ *this };
                ++*this;
                return ret;
            }
            auto operator*() const noexcept
            {
                if(lazy) {
                    cin >> val;
                    lazy = false;
                }
                return val;
            }
            auto operator->() const noexcept
            {
                if(lazy) {
                    cin >> val;
                    lazy = false;
                }
                return std::addressof(val);
            }
            mutable T val{ read<T>() };
            mutable bool lazy{};
        };

        constexpr static int n{ 640000 };
        static inline char buffer[n], *l{ buffer }, *r{ l };
        static istream cin;
        static inline bool normal{ true };

        operator bool()
        {
            return normal;
        }

        auto static get() -> char
        {
            if(l == r) {
                if(r = (l = buffer) + fread(buffer, 1, n, stdin); l == r) {
                    normal = false;
                    return *l;
                }
            }
            return *l++;
        }

        auto static get(char &c) -> istream&
        {
            c = get();
            return cin;
        }

        auto static peek() -> char
        {
            return *l;
        }

        auto static ignore()
        {
            ++l;
        }

        auto static unget()
        {
            --l;
        }

        template<typename T>
        auto static read() -> T
        {
            T ret;
            cin >> ret;
            return ret;
        }

        auto friend operator>>(istream& is,char& c) -> istream&
        {
            while(normal and isspace(c = get())) {}
            return is;
        }

#if __cplusplus >= 202002L
        template<std::integral T>
#else
        template<typename T>
#endif
        auto friend operator>>(istream& is, T& v) -> istream&
        {
            bool negative{};
            char c{};
            while(get(c) and isspace(c)) {}
            if(!normal) {
                return is;
            }
            if(c == '-') {
                negative = true;
                if(!get(c) or c < '0' or c > '9') {
                    return is;
                }
            }
            v = T{};
            do {
                v = v * 10 + (c ^ 48);
            }while(get(c) and c >= '0' and c <= '9');
            if(negative) {
                v = -v;
            }
            if(normal) {
                unget();
            }
            return is;
        }
    private:
        istream() = default;
    };

}
fasti::istream fasti::istream::cin;
auto& cin =  fasti::istream::cin;
template<typename T>
using fiterator = fasti::istream::iterator<T>;