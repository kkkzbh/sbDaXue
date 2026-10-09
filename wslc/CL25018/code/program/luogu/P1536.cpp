

#include<iostream>
#include<array>

struct set
{
    constexpr static int M_size{ 1000 + 2 };
    std::array<int,M_size> a{};
    int n{};
    set() = default;
    set(int n) : n(n){}
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
    int solve()
    {
        int ret{};
        for(int i = 1; i <= n;++i)
        {
            if(a[i] <= 0)
                ++ret;
        }
        return ret;
    }
    void clear()
    {
        for(int i = 1; i <= n;++i)
            a[i] = 0;
    }
    void reset(int x)
    {
        clear();
        n = x;
    }
};


int main()
{
    std::ios::sync_with_stdio(0),std::cout.tie(0),std::cin.tie(0);
    int n,m;
    set s;
    while(std::cin >> n)
    {
        if(!n)
            break;
        s.reset(n);
        std::cin >> m;
        while(m--)
        {
            int x,y;
            std::cin >> x >> y;
            s.merge(x,y);
        }
        std::cout << s.solve() - 1 << '\n';
    }



    return 0;
}