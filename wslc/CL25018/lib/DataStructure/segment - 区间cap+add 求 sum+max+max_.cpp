

struct segment
{
    using i64 = std::int64_t;
    auto static constexpr INF = std::numeric_limits<int>::max();

    template<typename It>
    auto build(int i,int il,int ir,It it) -> void
    {
        if(ir - il == 1) {
            sum1[i] = max1[i] = max_1[i] = it[il];
            cnt[i] = 1;
            return;
        }
        auto mid = (il + ir) / 2;
        build(left(i),il,mid,it);
        build(right(i),mid,ir,it);
        merge(i);
    }

    template<typename R>
    explicit segment(R&& r)
    : n(r.size()),sum1(4 * r.size()),max1(4 * r.size()),semax1(4 * r.size()),cnt(4 * r.size()),
    max_1(4 * r.size()),lz1(4 * r.size()),lz2(4 * r.size()),lz1_(4 * r.size()),lz2_(4 * r.size())
    { build(0,0,n,std::begin(r)); }

    auto merge(int i) -> void
    {
        auto li = left(i),ri = right(i);
        sum1[i] = sum1[li] + sum1[ri];
        if(max1[li] > max1[ri]) {
            max1[i] = max1[li];
            semax1[i] = std::max(semax1[li],std::optional{ max1[ri] });
            cnt[i] = cnt[li];
        } else if(max1[li] == max1[ri]) {
            max1[i] = max1[li];
            semax1[i] = std::max(semax1[li],semax1[ri]);
            cnt[i] = cnt[li] + cnt[ri];
        } else {
            max1[i] = max1[ri];
            semax1[i] = std::max(std::optional{ max1[li] },semax1[ri]);
            cnt[i] = cnt[ri];
        }
        max_1[i] = std::max(max_1[li],max_1[ri]);
    }

    auto add(int l,int r,int v) -> void
    {
        auto impl = [&](auto&& impl,int i,int il,int ir) -> void {
            if(il >= l and ir <= r) {
                auto sz = i64(ir - il);
                sum1[i] += sz * v;
                max1[i] += v;
                if(semax1[i]) {
                    *semax1[i] += v;
                }
                lz1_[i] = std::max(lz1_[i],lz1[i] += v);
                lz2_[i] = std::max(lz2_[i],lz2[i] += v);
                max_1[i] = std::max(max_1[i],max1[i]);
                return;
            }
            down(i,il,ir);
            auto mid = (il + ir) / 2;
            if(l < mid) {
                impl(impl,left(i),il,mid);
            }
            if(r > mid) {
                impl(impl,right(i),mid,ir);
            }
            merge(i);
        };
        impl(impl,0,0,n);
    }

    auto cap(int l,int r,int v) -> void
    {
        auto impl = [&](auto&& impl,int i,int il,int ir) -> void {
            if(v >= max1[i]) {
                return;
            }
            if(il >= l and ir <= r and v > semax1[i].value_or(-INF)) {
                auto delta = max1[i] - v;
                sum1[i] -= 1LL * delta * cnt[i];
                lz1[i] -= delta;
                max1[i] = v;
                return;
            }
            down(i,il,ir);
            auto mid = (il + ir) / 2;
            if(l < mid) {
                impl(impl,left(i),il,mid);
            }
            if(r > mid) {
                impl(impl,right(i),mid,ir);
            }
            merge(i);
        };
        impl(impl,0,0,n);
    }

    auto down(int i,int il,int ir) -> void
    {
        auto li = left(i),ri = right(i);
        auto m = std::max(max1[li],max1[ri]);
        auto mid = (il + ir) / 2;
        auto impl = [&](int k,int sz) {
            auto [k1,k2,k3,k4] = std::make_tuple(lz1[i],lz2[i],lz1_[i],lz2_[i]);
            if(m != max1[k]) { // 如果不存在最大值
                k1 = k2;
                k3 = k4;
            }
            max_1[k] = std::max(max_1[k],max1[k] + k3);
            lz1_[k] = std::max(lz1_[k],lz1[k] + k3);
            lz2_[k] = std::max(lz2_[k],lz2[k] + k4);
            max1[k] += k1;
            if(semax1[k]) {
                *semax1[k] += k2;
            }
            sum1[k] += 1LL * cnt[k] * k1;
            sum1[k] += 1LL * (sz - cnt[k]) * k2;
            lz1[k] += k1;
            lz2[k] += k2;
        };
        impl(li,mid - il),impl(ri,ir - mid);
        lz1[i] = lz2[i] = lz1_[i] = lz2_[i] = 0; // 清空懒
    }

    auto sum(int l,int r) -> i64
    {
        auto impl = [&](auto&& impl,int i,int il,int ir) -> i64 {
            if(il >= l and ir <= r) {
                return sum1[i];
            }
            down(i,il,ir);
            auto val = 0LL;
            auto mid = (il + ir) / 2;
            if(l < mid) {
                val += impl(impl,left(i),il,mid);
            }
            if(r > mid) {
                val += impl(impl,right(i),mid,ir);
            }
            return val;
        };
        return impl(impl,0,0,n);
    }

    auto max(int l,int r) -> int
    {
        auto impl = [&](auto&& impl,int i,int il,int ir) -> int {
            if(il >= l and ir <= r) {
                return max1[i];
            }
            down(i,il,ir);
            auto val = std::numeric_limits<decltype(max1[i] + 0)>::min();
            auto mid = (il + ir) / 2;
            if(l < mid) {
                val = impl(impl,left(i),il,mid);
            }
            if(r > mid) {
                val = std::max(val,impl(impl,right(i),mid,ir));
            }
            return val;
        };
        return impl(impl,0,0,n);
    }

    auto max_(int l,int r) -> int
    {
        auto impl = [&](auto&& impl,int i,int il,int ir) -> int {
            if(il >= l and ir <= r) {
                return max_1[i];
            }
            down(i,il,ir);
            auto val = std::numeric_limits<decltype(max_1[i] + 0)>::min();
            auto mid = (il + ir) / 2;
            if(l < mid) {
                val = impl(impl,left(i),il,mid);
            }
            if(r > mid) {
                val = std::max(val,impl(impl,right(i),mid,ir));
            }
            return val;
        };
        return impl(impl,0,0,n);
    }

    int n;
    std::vector<i64> sum1;
    std::vector<int> max1,cnt,max_1;
    std::vector<std::optional<int>> semax1;
    std::vector<int> lz1,lz2,lz1_,lz2_;

    auto static constexpr explanatory_variable = R"(
        lz1 : 最大值加法标记
        lz2 : 其他值加法标记
        后缀_表示历史最大
    )";

    auto static left(int i) -> int
    { return i << 1 | 1; }

    auto static right(int i) -> int
    { return left(i) + 1; }
};