

#include <bits/stdc++.h>

using i64 = long long;

template<typename T = i64>
struct segment
{

    auto static left(int i) -> int
    { return i << 1 | 1; }

    auto static right(int i) -> int
    { return left(i) + 1; }

    auto build(int i,int l,int r,auto const& vec) -> void
    {
        tab[i] = std::make_pair(l,r);
        if(r - l == 1) {
            a[i] = vec[l];
            return;
        }
        auto mid = (l + r) / 2;
        build(left(i),l,mid,vec);
        build(right(i),mid,r,vec);
        merge(i);
    }

    explicit segment(size_t n) : a(4 * n),lz(4 * n),tab(4 * n) {}

    explicit segment(auto const& vec)
    : segment(vec.size())
    { build(0,0,vec.size(),vec); }

    auto merge(int i) -> void
    { a[i] = a[left(i)] + a[right(i)]; }

    auto update(int i) -> void
    {
        if(lz[i]) {
            auto li = left(i),ri = right(i);
            lz[li] += lz[i];
            lz[ri] += lz[i];
            auto const& [l1,r1] = tab[li];
            auto const& [l2,r2] = tab[ri];
            a[li] += (r1 - l1) * lz[i];
            a[ri] += (r2 - l2) * lz[i];
            lz[i] = 0;
        }
    }

    auto add(int i,int l,int r,auto val) -> void
    {
        auto const& [il,ir] = tab[i];
        if(il >= l and ir <= r) {
            a[i] += 1LL * (ir - il) * val;
            lz[i] += val;
            return;
        }
        update(i);
        auto mid = (il + ir) / 2;
        if(l < mid) {
            add(left(i),l,r,val);
        }
        if(r > mid) {
            add(right(i),l,r,val);
        }
        merge(i);
    }

    auto add(int l,int r,auto val) -> void
    { add(0,l,r,val); }

    auto sum(int i,int l,int r) -> i64
    {
        auto const& [il,ir] = tab[i];
        if(il >= l and ir <= r) {
            return a[i];
        }
        update(i);
        auto mid = (il + ir) / 2;
        auto ret = 0LL;
        if(l < mid) {
            ret += sum(left(i),l,r);
        }
        if(r > mid) {
            ret += sum(right(i),l,r);
        }
        return ret;
    }

    auto sum(int l,int r) -> i64
    { return sum(0,l,r); }


    std::vector<T> a,lz;
    std::vector<std::pair<int,int>> tab;
};


auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    std::cin >> n >> m;
    auto a = std::vector(n,0LL);
    for(auto& val : a) {
        std::cin >> val;
    }
    auto seg = segment{ a };
    for(auto i = 0; i != m; ++i) {
        int c;
        std::cin >> c;
        if(c == 1) {
            int x,y;
            i64 k;
            std::cin >> x >> y >> k;
            --x;
            seg.add(x,y,k);
        } else if(c == 2) {
            int x,y;
            std::cin >> x >> y;
            --x;
            std::cout << seg.sum(x,y) << '\n';
        }
    }

    return 0;
}