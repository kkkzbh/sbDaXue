

template<typename Cmp,typename Proj>
struct cartesian_tree
{

    auto static constexpr null = 0;

    template<typename C = std::less,typename P = std::identity>
    explicit cartesian_tree(std::span<int> data,C&& cmp = {},P&& proj = {})
    : a(data),left(a.size() + 1,null),right(a.size() + 1,null),cmp(std::forward<C>(cmp)),proj(std::forward<P>(proj))
    {
        for(auto const i : iota(1) | take(a.size())) {
            auto const v = a[i - 1];
            auto it = null;
            while(not stk.empty() and cmp(proj(v),proj(std::get<1>(stk.back())))) {
                it = std::get<0>(stk.back());
                stk.pop_back();
            }
            if(it != null) {
                left[i] = it;
            }
            if(not stk.empty()) {
                right[std::get<0>(stk.back())] = i;
            }
            stk.emplace_back(i,v);
        }
        r = std::get<0>(stk.front());
    }

    int r;
    std::span<int> a;
    std::vector<int> left;
    std::vector<int> right;
    std::vector<std::pair<int,int>> stk; // i(小根堆) v(搜索树 节点编号)
    Cmp cmp;
    Proj proj;
};

template<typename C,typename P>
cartesian_tree(std::span<int> data,C&& cmp,P&& proj) -> cartesian_tree<std::remove_cvref_t<C>,std::remove_cvref_t<P>>;
