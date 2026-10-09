

#include <bits/stdc++.h>

template<typename Cmp>
struct segment
{
    template<typename Vec>
    explicit segment(Vec const& v,Cmp cmp_fn) : n(v.size()),max(n * 4),lz(n * 4),av(v),cmp(cmp_fn)
    {
        auto build = [&](auto&& self,int i,int l,int r) -> void {
            if(l + 1 == r) {
                max[i] = l;
                return;
            }
            auto mid = (l + r) / 2;
            self(self,left(i),l,mid);
            self(self,right(i),mid,r);
            merge(i);
        };
        build(build,0,0,n);
    }

    auto merge(int i) -> void
    {
        auto li = left(i),ri = right(i);
        max[i] = std::max(max[li],max[ri],cmp);
    }

    auto lazy(int i,int val) -> void
    {
        max[i] = val;
        lz[i] = val;
    }

    auto modify(int l,int r,int val) -> void
    {
        auto impl = [&](auto&& self,int i,int il,int ir) -> void {
            if(il >= ir or ir <= l or il >= r) {
                return;
            }
            if(il >= l and ir <= r) {
                lazy(i,val);
                return;
            }
            down(i);
            auto mid = (il + ir) / 2;
            self(self,left(i),il,mid);
            self(self,right(i),mid,ir);
            merge(i);
        };
        impl(impl,0,0,n);
    }

    auto query(int l,int r)
    {
        using return_type = int;
        auto impl = [&](auto&& self,int i,int il,int ir) -> return_type {
            if(ir <= l or il >= r) {
                return n;
            }
            if(il >= l and ir <= r) {
                return max[i];
            }
            auto mid = (il + ir) / 2;
            return std::max(self(self,left(i),il,mid),self(self,right(i),mid,ir),cmp);
        };
        return impl(impl,0,0,n);
    }

    auto down(int i) -> void
    {
        if(lz[i]) {
            auto lv = *lz[i];
            lz[i] = {};
            lazy(left(i),lv);
            lazy(right(i),lv);
        }
    }

    int n;
    std::vector<int> max;
    std::vector<std::optional<int>> lz; // max
    std::vector<int> const& av;
    Cmp cmp;

    auto static left(int i) -> int
    { return (i * 2) | 1; }

    auto static right(int i) -> int
    { return left(i) + 1; }

};

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,k;
    std::cin >>  n >> k;
    auto a = std::vector(n,0);
    for(auto& v : a) {
        std::cin >> v;
    }
    auto constexpr INF = std::numeric_limits<int>::min();
    auto cmp = [&,impl = std::less{}](int li,int ri) -> int {
        return impl(a[li],a[ri]);
    };
    auto seg = segment{ a,cmp };
    a.emplace_back(INF);
    auto buc = std::vector(n,-1);
    auto preval = -1;
    auto que = std::vector<std::pair<int,int>>{};
    for(auto i = 0; i != n; ) {
        auto r = i + k + 1;
        auto it = seg.query(i,std::min(r,n));
        auto val = a[it];
        if(val == INF) {
            preval = -1;
            ++i;
        } else {
            if(val == preval) {
                que.emplace_back(it,val);
                a[it] = INF;
                seg.modify(it,it + 1,it);
                continue;
            }
            preval = val;
            a[it] = INF;
            seg.modify(it,it + 1,it);
            buc[i] = val;
            k -= it - i;
            ++i;
        }
        for(auto const& [index,value] : que) {
            a[index] = value;
            seg.modify(index,index + 1,index);
        }
        que.clear();
    }

    for(auto v : buc) {
        std::cout << v << ' ';
    }

}