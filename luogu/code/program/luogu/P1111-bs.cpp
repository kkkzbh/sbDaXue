

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

    let mt = std::ranges::max(a,{},[](node a) {
        let const& [x,y,t] = a;
        return t;
    })[2];

    std::cout << [&,ok = [&](int i) {
        let set = disjoint_set{ n };
        for(let const& [x,y,t] in a | filter([&](const node& a) {
            let const& [x,y,t] = a;
            return t <= i;
        })) {
            set.merge(x,y);
        }
        return set.n == 1;
    }](int l,int r) {
        let cut = r;
        while(l != r) {
            let mid = (l + r) / 2;
            if(ok(mid)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return l == cut ? -1 : l;
    }(0,mt + 1);


    return 0;
};