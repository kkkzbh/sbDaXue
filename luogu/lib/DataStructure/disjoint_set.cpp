struct disjoint_set
{
    template<std::integral I>
    explicit disjoint_set(I n) : a(std::vector<int>(n,-1)),n{ n }{}

    fun find(int i) -> int
    {
        if(a[i] >= 0) {
            return a[i] = find(a[i]);
        }
        return i;
    }

    fun merge(int x,int y) -> bool
    {
        int fx{ find(x) };
        int fy{ find(y) };
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

    fun same(int x,int y) -> bool
    {
        return find(x) == find(y);
    }

    std::vector<int> a;
    int n;
};