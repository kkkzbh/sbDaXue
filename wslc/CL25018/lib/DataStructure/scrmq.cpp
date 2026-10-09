template<typename T,typename Cmp = std::less<>>
struct scrmq
{
    auto static constexpr blocks = 64u;

    explicit scrmq(std::vector<T> const& d,Cmp&& cmp = {})
    : n(d.size()),pre(d),suf(d),a(d),stk(n),cmp(std::forward<Cmp>(cmp))
    {
        if(not n) {
            return;
        }
        auto const m = (n - 1) / blocks + 1;
        auto const p = std::bit_width(m);
        st.assign(p,std::vector(m,T{}));
        for(auto const [i,v] : a | chunk(blocks) | enumerate) {
            st[0][i] = std::ranges::min(v,cmp);
        }
        for(auto v : pre | chunk(blocks)) {
            for(auto [front,back] : v | pairwise) {
                back = std::min(back,front,cmp);
            }
        }
        for(auto v : suf | chunk(blocks) | reverse) {
            for(auto [front,back] : v | reverse | pairwise) {
                back = std::min(back,front,cmp);
            }
        }
        for(auto const k : iota(1,p)) {
            auto not_over = [&](auto const i) {
                return i + (1 << k) <= m;
            };
            for(auto const i : iota(0) | take(m) | take_while(not_over)) {
                st[k][i] = std::min(st[k - 1][i],st[k - 1][i + (1 << (k - 1))],cmp);
            }
        }
        for(auto r : iota(0,n) | chunk(blocks)) {
            auto s = 0ULL;
            auto const l = r.front();
            for(auto const i : r) {
                while(s and cmp(a[i],a[l + std::__lg(s)])) {
                    s ^= 1ULL << std::__lg(s); // 出栈
                }
                s |= 1Ull << (i - l); // 入栈
                stk[i] = s; // 保存状态
            }
        }
    }

    auto operator()(int const l,int const r) const -> T // 左闭右开
    {
        if(l / blocks != (r - 1) / blocks) { // 非同块
            auto ans = std::min(suf[l],pre[r - 1],cmp);
            auto const bl = l / blocks + 1; // 新块起始 包含
            auto const br = r / blocks; // 尾 不包含
            if(l < r) { // 有块间隔
                auto k = std::__lg(br - bl); // 下取整
                ans = std::min({ ans,st[k][l],st[k][l - (1 << k)] },cmp);
                return ans;
            }
        } else { // 同块
            auto const first = blocks * (l / blocks); // 块起点 重点是单调栈[l,r)的状态(栈顶)
            return a[std::countr_zero(stk[r - 1] >> (l - first)) + l];
        }
    }

    int n;
    std::vector<std::vector<T>> st;
    std::vector<T> pre,suf,a;
    std::vector<u64> stk;
    Cmp cmp{};
};