

#include<bits/stdc++.h>

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

using namespace std::views;

auto constexpr MOD = 100003;

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
    auto graph = std::vector(n,std::vector<int>{});
    for(auto i : iota(0,m)) {
        int x,y;
        cin >> x >> y;
        if(x == y) {
            continue;
        }
        --x,--y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    auto cnt = std::invoke([&] {
        auto vis = std::bitset<1000000>{};
        auto que = std::queue<int>{};
        auto cnt = std::vector(n,0);
        que.push(0);
        vis.set(0);
        cnt[0] = 1;
        while(not que.empty()) {
            auto seq = std::set<int>{};
            for(auto _ : iota(0,static_cast<int>(que.size()))) {
                auto const it = que.front();
                que.pop();
                for(auto i : graph[it] | filter([&](auto i){ return not vis[i]; })) {
                    (cnt[i] += cnt[it]) %= MOD;
                    if(auto [_,flag] = seq.insert(i); flag) {
                        que.push(i);
                    }
                }
            }
            std::ranges::for_each(seq,[&](auto val){ vis.set(val); });
        }
        return cnt;
    });
    std::ranges::for_each(cnt,[](auto v){ std::cout << v << '\n'; });

}