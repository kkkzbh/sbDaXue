struct cartesian_tree
{

    auto static constexpr null = -1;

    explicit cartesian_tree(std::span<int> data)
    : a(data),left(a.size(),null),right(a.size(),null)
    {
        for(auto const i : iota(0) | take(a.size())) {
            auto const v = a[i];
            auto it = null;
            while(not stk.empty() and std::less{}(v,std::get<1>(stk.top()))) {
                it = std::get<0>(stk.top());
                stk.pop();
            }
            if(it != null) {
                left[i] = it;
            }
            if(not stk.empty()) {
                right[std::get<0>(stk.top())] = i;
            }
            stk.emplace(i,v);
        }
        while(stk.size() != 1) {
            stk.pop();
        }
        r = std::get<0>(stk.top());
    }

    int r;
    std::span<int> a;
    std::vector<int> left,right;
    std::stack<std::pair<int,int>> stk;
};