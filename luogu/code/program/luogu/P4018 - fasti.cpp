

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
#include<unordered_set>
#include<cassert>

#define fun auto
#define var auto
#define cast static_cast
#define range(A) A.begin(),A.end()

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;
using namespace std::views;

constexpr int INF{ 1000000000 + 520 };
constexpr int64 LNF { 66666666666666666 };

namespace fasti
{
    struct istream
    {
        constexpr static int n{ 640000 };
        static inline char buffer[n], *l{ buffer }, *r{ l };

        fun get() -> char
        {
            if(l == r) {
                r = (l = buffer) + fread(buffer, n, 1, stdin);
            }
            return *l++;
        }

        fun get(char &c) -> istream&
        {
            if(l == r) {
                r = (l = buffer) + fread(buffer, 1, n, stdin);
            }
            c = *l++;
            return *this;
        }

        fun peek() -> char
        {
            if(l == r) {
                r = (l = buffer) + fread(buffer, 1, n, stdin);
            }
            return *l;
        }

        fun ignore()
        {
            if(l == r) {
                r = (l = buffer) + fread(buffer, 1, n, stdin);
            }
            ++l;
        }

        template<std::integral T>
        fun next() -> T
        {
            T v{};
            *this >> v;
            return v;
        }

        fun friend operator>>(istream& is,char& c)
        {
            c = is.get();
            return is;
        }

        template<std::integral T>
        fun friend operator>>(istream& is, T& v)
        {
            v = T{};
            while(isspace(is.peek())) {
                is.ignore();
            }
            for(char c{ is.get() }; c >= '0' and c <= '9'; c = is.get()) {
                v = (v * 10) + (c ^ 48);
            }
            return is;
        }
    };
}
fasti::istream cin;

constexpr const char* ans[2]{ "Roy wins!","October wins!" };

fun solve()
{
    int n;
    cin >> n;
    std::cout << ans[(n % 6) != 0] << '\n';
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--) {
        std::invoke(solve);
    }
}