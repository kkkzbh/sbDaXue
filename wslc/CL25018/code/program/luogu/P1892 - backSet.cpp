


#include<iostream>
#include<array>

struct disjoint_set
{
    constexpr static int M_size{ 2000 + 2 };
    std::array<int,M_size> a;
    disjoint_set(){ a.fill(-1); }
    int find(int x)
    {
        if(a[x] > -1)
            return a[x] = find(a[x]);
        return x;
    }
    void merge(int x,int y)
    {
        int fx = find(x);
        int fy = find(y);
        if(fx == fy)
            return;
        if(fx < fy)
        {
            a[fy] = fx;
        }
        else
        {
            a[fx] = fy;
        }
    }
    bool same(int x,int y)
    {
        return find(x) == find(y);
    }
};

disjoint_set set;

int main()
{
    int n,m;
    std::cin >> n >> m;
    for(int i{}; i != m;++i)
    {
        char op;
        int p,q;
        if(std::cin >> op >> p >> q; op == 'F')
        {
            set.merge(p,q);
        }
        else
        {
            set.merge(p,n + q);
            set.merge(q,n + p);
        }
    }
    std::size_t ans{};
    for(int i{ 1 }; i <= n;++i)
    {
        if(set.a[i] < 0)
            ++ans;
    }
    std::cout << ans;


    return 0;
}