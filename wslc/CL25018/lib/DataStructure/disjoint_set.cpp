struct disjoint_set
{
    explicit disjoint_set(std::integral auto n) : a(n,-1),n(n) {}

    auto find(int i) -> int
    { return a[i] < 0 ? i : a[i] = find(a[i]); }

    auto merge(int x,int y) -> bool
    {
        auto fx = find(x),fy = find(y);
        if(fx != fy) {
            if(a[fx] < a[fy]) {
                a[fx] += a[fy];
                a[fy] = fx;
            } else {
                a[fy] += a[fx];
                a[fx] = fy;
            }
            --n;
            return true;
        }
        return false;
    }

    auto same(int x,int y) -> bool
    {
        return find(x) == find(y);
    }

    auto count(int x) -> int
    { return -a[find(x)]; }

    std::vector<int> a;
    int n;
};