

#include <bits/stdc++.h>

using i64 = std::int64_t;

struct segment
{

    template<std::integral I>
    explicit segment(I n) : s(4 * n),max(4 * n),semax(4 * n),cnt(4 * n) {}

    template<std::ranges::random_access_range range>
    explicit segment(range const& vec) : segment(vec.size())
    { build(0,0,vec.size(),vec); }

    template<std::ranges::random_access_range range>
    auto build(int i,int il,int ir,range const& vec) -> void
    {
        if(ir - il == 1) {
            s[i] = max[i] = vec[il];
            semax[i] = INT_MIN;
            cnt[i] = 1;
            return;
        }
        auto mid = (il + ir) / 2;
        build(left(i),il,mid,vec);
        build(right(i),mid,ir,vec);
        merge(i);
    }

    auto merge(int i) -> void
    {
        auto li = left(i),ri = right(i);
        s[i] = s[li] + s[ri];
        max[i] = std::ranges::max(max[li],max[ri]);
        auto ret = max[li] <=> max[ri];
        if(ret == 0) {
            semax[i] = std::ranges::max(semax[li],semax[ri]);
            cnt[i] = cnt[li] + cnt[ri];
        } else if(ret > 0) {
            semax[i] = std::ranges::max(semax[li],max[ri]);
            cnt[i] = cnt[li];
        } else {
            semax[i] = std::ranges::max(max[li],semax[ri]);
            cnt[i] = cnt[ri];
        }
    }

    template<bool tag = true>
    auto update(int i,int val) -> void
    {
        if constexpr (tag) {
            if(val >= max[i]) {
                return;
            }
        }
        s[i] -= 1LL * cnt[i] * (max[i] - val);
        max[i] = val;
    }

    auto down(int i) -> void
    {
        update<true>(left(i),max[i]);
        update<true>(right(i),max[i]);
    }

    auto modify(int l,int r,int val) -> void
    {
        return
        [this,l,r,val](this auto&& self,int i,int il,int ir) {
            if(val >= max[i]) {
                return;
            }
            if(il >= l and ir <= r and val > semax[i]) {
                update<false>(i,val);
                return;
            }
            down(i);
            auto mid = (il + ir) / 2;
            if(l < mid) {
                self(left(i),il,mid);
            }
            if(r > mid) {
                self(right(i),mid,ir);
            }
            merge(i);
        }(0,0,s.size() / 4);
    }

    struct sum_tag_t {};
    struct max_tag_t {};

    constexpr static sum_tag_t sum_tag{};
    constexpr static max_tag_t max_tag{};

    auto operator()(sum_tag_t,int l,int r) -> i64
    {
        return
        [this,l,r](this auto&& self,int i,int il,int ir) -> i64 {
            if(il >= l and ir <= r) {
                return s[i];
            }
            down(i);
            auto ret = i64{};
            auto mid = (il + ir) / 2;
            if(l < mid) {
                ret += self(left(i),il,mid);
            }
            if(r > mid) {
                ret += self(right(i),mid,ir);
            }
            return ret;
        }(0,0,s.size() / 4);
    }

    auto operator()(max_tag_t,int l,int r) -> int
    {
        return
        [this,l,r](this auto&& self,int i,int il,int ir) -> int {
            if(il >= l and ir <= r) {
                return max[i];
            }
            down(i);
            auto ret = INT_MIN;
            auto mid = (il + ir) / 2;
            if(l < mid) {
                ret = std::ranges::max(ret,self(left(i),il,mid));
            }
            if(r > mid) {
                ret = std::ranges::max(ret,self(right(i),mid,ir));
            }
            return ret;
        }(0,0,s.size() / 4);
    }

    auto static left(int i) -> int
    { return i << 1 | 1; }

    auto static right(int i) -> int
    { return left(i) + 1; }

    std::vector<i64> s;
    std::vector<int> max,semax,cnt;
};

auto solve()
{
    int n,m;
    std::cin >> n >> m;
    auto a = std::vector(n,0);
    for(auto& val : a) {
        std::cin >> val;
    }
    auto seg = segment{ a };
    for(auto i = 0; i != m; ++i) {
        int c,x,y;
        std::cin >> c >> x >> y;
        --x;
        switch(c) {
            case 0: {
                int t;
                std::cin >> t;
                seg.modify(x,y,t);
                break;
            } case 1: {
                std::cout << seg(segment::max_tag,x,y) << '\n';
                break;
            } case 2: {
                std::cout << seg(segment::sum_tag,x,y) << '\n';
                break;
            }
        }
    }
}

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    for(auto i = 0; i != t; ++i) {
        solve();
    }

    return 0;
}
