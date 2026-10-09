

#include<bits/stdc++.h>

#define fun auto
#define let auto
#define in :

struct disjoint_set
{

    disjoint_set(int n) : a(n)
    { std::iota(a.begin(),a.end(),0); }

    fun find(int i) -> int
    { return a[i] == i ? i : a[i] = find(a[i]); }

    fun merge(int x,int y)
    { a[find(y)] = find(x); }

    fun same(int x,int y)
    { return find(x) == find(y); }

    std::vector<int> a;
};

struct node
{
    fun friend operator>>(auto& is,node& n) -> auto&
    { return is >> n.x >> n.y; }
    node() = default;
    node(int xx,int yy) : x{ xx },y{ yy } {}
    int x,y;
};

fun main() -> signed
{
    int n,m;
    std::cin >> n >> m;
    let a = std::vector(m,node{});
    for(let &v in a) {
        std::cin >> v;
    }

    let rev = std::vector(n,false);

    let build = [&,n] {
        let set = disjoint_set{ n };
        for(let [x,y] in a) {
            set.merge(x,y);
        }
        let ret = 0;
        for(int i{}; i != n; ++i) {
            if(!rev[i] and set.a[i] == i) {
                ++ret;
            }
        }
        return ret;
    };

    let remove = [&](int i) {
        let bound = std::remove_if(a.begin(),a.end(),[i](node v){ return v.x == i or v.y == i; });
        a.erase(bound,a.end());
        rev[i] = true;
    };

    int k;
    std::cin >> k;
    let kv = k;
    for(let it = build(); k--;) {
        int v;
        std::cin >> v;
        remove(v);
        let newit = build();
        if(newit > it) {
            std::cout << "Red Alert: ";
        }
        std::cout << "City " << v << " is lost" << ".!"[newit > it] << '\n';
        it = newit;
    }
    if(kv == n) {
        std::cout << "Game Over.";
    }


    return 0;
}