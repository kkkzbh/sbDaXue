

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
    explicit disjoint_set(I n) : a(std::vector<int>(n,-1)){}

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
            return true;
        }
        return false;
    }

    fun same(int x,int y) -> bool
    {
        return find(x) == find(y);
    }

    std::vector<int> a;
};

struct node
{
    int x,y,weight;
};

fun kruskal(std::vector<node>& side,int n) -> std::optional<int>
{
    let set = disjoint_set{ n };
    std::ranges::sort(side,[](node x,node y){ return x.weight < y.weight; });
    let cnt = 0;
    let ans = 0;
    for(let [x,y,weight] in side) {
        if(set.merge(x,y)) {
            ans += weight;
            ++cnt;
        }
    }
    if(cnt == n - 1) {
        return ans;
    }
    return {};
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);

    int n,m;
    std::cin >> n >> m;
    let a = std::vector(m,node{});
    for(let &[x,y,weight] in a) {
        std::cin >> x >> y >> weight;
        --x,--y;
    }
    let ans = kruskal(a,n);
    if(ans) {
        std::cout << *ans;
    } else {
        std::cout << "orz";
    }

    return 0;
}


