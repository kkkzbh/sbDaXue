

#include<iostream>

struct set
{
    constexpr static int M_size{ 5000 + 2 };
    int a[M_size]{};

    int find(int x)
    {
        if(a[x] > 0)
            return a[x] = find(a[x]);
        return x;
    }
    void merge(int x,int y)
    {
        int fx = find(x);
        int fy = find(y);
        if(fx != fy)
        {
            if(fx < fy)
                a[fx] = fy;
            else
                a[fy] = fx;
        }
    }
    bool same(int x,int y)
    {
        return find(x) == find(y);
    }
};

constexpr char ans[][5]{"No\n","Yes\n"};

int main()
{
    freopen("../in","r",stdin);
    freopen("../out","w",stdout);
    std::ios::sync_with_stdio(0),std::cout.tie(0),std::cin.tie(0);
    int n,m,p;
    std::cin >> n >> m >> p;
    set s;
    for(int i = 0; i != m;++i)
    {
        int x,y;
        std::cin >> x >> y;
        s.merge(x,y);
    }
    for(int i = 0; i != p;++i)
    {
        int x,y;
        std::cin >> x >> y;
        std::cout << ans[s.same(x,y)];
    }


    return 0;
}