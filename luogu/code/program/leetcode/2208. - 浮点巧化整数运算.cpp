

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
using namespace std;

constexpr int INF{ 1000000000 + 520 };
constexpr int64 LNF { 66666666666666666 };

template<typename T>
concept STD_array = requires(T array)
{
    typename T::value_type;
    { array[0] } -> std::same_as<std::add_lvalue_reference<typename T::value_type>>;
};

template<typename T>
concept Array = STD_array<T> or std::is_array_v<T>;

template<typename... Args>
fun print(const std::format_string<Args...> fmts,Args&&... args)
{
    std::cout << std::vformat(fmts.get(), std::make_format_args(args...));
}

template<typename T>
fun print(T&& arg)
{
    print("{}",arg);
}

fun println()
{
    print('\n');
}

template<typename... Args>
fun println(const std::format_string<Args...> fmts,Args&&... args)
{
    print(fmts,std::forward<Args>(args)...);
    println();
}

template<typename T>
fun println(T&& arg)
{
    println("{}",arg);
}

class Solution {
public:
    int halveArray(vector<int>& a)
    {
        std::priority_queue<int64> que;
        for(int64 v : a) {
            que.push((1 << 21) * v);
        }
        int64 sum{ std::accumulate(range(a),int64{}) };
        sum *= (1 << 20);
        int ans{};
        while(sum > 0) {
            int64 val{ que.top() / 2ll };
            que.pop();
            sum -= val;
            que.push(val);
            ++ans;
        }
        return ans;
    }
};