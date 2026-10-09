

#include<bits/stdc++.h>

#define fun auto
#define let auto
#define in :

using int64 = long long;
using uint64 = unsigned long long;
using double128 = long double;

using namespace std::ranges::views;

constexpr int INF = std::numeric_limits<decltype(INF)>::max();
constexpr int64 INF64 = std::numeric_limits<decltype(INF64)>::max();


fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    let a = std::vector(n,0);
    for(let &v in a) {
        std::cin >> v;
    }

    let max_que = std::priority_queue<int>{};
    let min_que = std::priority_queue<int,std::vector<int>,std::greater<>>{};

    for(let v in a) {
        max_que.push(v);
        min_que.push(v);
    }

    let min = 0;
    let max = 0;
    while(max_que.size() != 1) {
        let x = max_que.top();
        max_que.pop();
        let y = max_que.top();
        max_que.pop();
        max += x + y;
        max_que.push(x + y);
    }

    while(min_que.size() != 1) {
        let x = min_que.top();
        min_que.pop();
        let y = min_que.top();
        min_que.pop();
        min += x + y;
        min_que.push(x + y);
    }

    std::cout << min << '\n' << max;

    return 0;
}


