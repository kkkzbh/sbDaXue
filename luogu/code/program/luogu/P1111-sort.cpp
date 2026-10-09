

#include<bits/extc++.h>

#define fun auto
#define let auto
#define in :

struct disjoint_set
{

    explicit disjoint_set(int n) : a(n,-1),n{ n } {}

    fun find(int i) -> int // NOLINT
    { return a[i] == -1 ? i : a[i] = find(a[i]); }

    fun same(int x,int y) -> bool
    { return find(x) == find(y); }

    fun merge(int x,int y) -> bool
    {
        let fx = find(x),fy = find(y);
        if(fx == fy) {
            return false;
        }
        a[fx] = fy;
        --n;
        return true;
    }

    std::vector<int> a;
    int n;
};


fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    using node = std::array<int,3>;
    let a = std::vector(m,node{});
    let scan = []<typename... T>(T&... vs) { (std::cin >> ... >> vs); };
    using namespace std::views;
    std::ranges::for_each(a | join,scan);
    std::ranges::for_each(a,[](node& a) {
        let &[x,y,t] = a;
        --x,--y;
    });
    std::ranges::sort(a,{},[](node a){
        let const& [x,y,t] = a;
        return t;
    });
    std::cout << [&] {
        let set = disjoint_set{ n };
        for(let const& [x,y,t] in a) {
            set.merge(x,y);
            if(set.n == 1) {
                return t;
            }
        }
        return -1;
    }();


    return 0;
};