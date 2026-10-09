

struct disjoint_set
{
    template<std::integral I>
    explicit disjoint_set(I n) : a(std::vector<int>(n,-1)){}

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
            return true;
        }
        return false;
    }

    fun same(int x,int y) -> bool
    {
        return find(x) == find(y);
    }

    std::vector<int> a;
};

struct node
{
    int x,y,weight;
};

fun kruskal(std::vector<node>& side,int n) -> std::optional<int>
{
let set = disjoint_set{ n };
std::ranges::sort(side,[](node x,node y){ return x.weight < y.weight; });
let cnt = 0;
let ans = 0;
for(let [x,y,weight] in side) {
if(set.merge(x,y)) {
ans += weight;
++cnt;
}
}
if(cnt == n - 1) {
return ans;
}
return {};
}