

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

struct disjoint_set
{
    template<std::integral I>
    explicit disjoint_set(I n) : a(std::vector<int>(n,-1)),n{ n }{}

    fun find(int i) -> int
    {
        if(a[i] >= 0) {
            return a[i] = find(a[i]);
        }
        return i;
    }

    fun merge(int x,int y) -> bool
    {
        int fx{ find(x) };
        int fy{ find(y) };
        if(fx != fy) {
            if(a[fx] < a[fy]) {
                a[fx] += a[fy];
                a[fy] = fx;
            } else {
                a[fy] += a[fx];
                a[fx] = fy;
            }
            --n;
            return true;
        }
        return false;
    }

    fun same(int x,int y) -> bool
    {
        return find(x) == find(y);
    }

    std::vector<int> a;
    int n;
};

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);

    int n,m,k;
    std::cin >> n >> m >> k;
    using node = std::array<int,3>; // x y l

    let a = std::vector(m,node{});
    for(let &[x,y,l] in a) {
        std::cin >> x >> y >> l;
    }

    std::ranges::sort(a,std::greater{},[](node v){ return v[2]; });

    let set = disjoint_set{ n };

    let ans = [&,k]() -> std::optional<int> {

        let ret = 0;
        while(not a.empty() and set.n > k) {
            let [x,y,l] = a.back();
            a.pop_back();
            if(!set.merge(x,y)) {
                continue;
            }
            ret += l;
        }

        if(set.n > k) {
            return {};
        }
        return ret;

    }();

    if(ans) {
        std::cout << *ans;
    } else {
        std::cout << "No Answer";
    }

    return 0;
}


