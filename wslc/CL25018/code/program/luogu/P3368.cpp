


#include<iostream>
#include<array>

struct Tarray
{
#define lb(i) (i & -i)
    using int64 = long long;

    constexpr static int N{ 500000 + 2 };
    std::array<int,N> a;
    int sz;

    void add(int l,int r,int val)
    {
        add(l,val);
        add(r + 1,-val);
    }

    void add(int pos,int val)
    {
        while(pos <= sz)
        {
            a[pos] += val;
            pos += lb(pos);
        }
    }

    int64 query(int pos)
    {
        int64 ret{};
        while(pos)
        {
            ret += a[pos];
            pos -= lb(pos);
        }
        return ret;
    }


};

Tarray a;

int main()
{
    int m;
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> a.sz >> m;
    for(int i{ 1 },l{},r{}; i <= a.sz; ++i)
    {
        l = r;
        std::cin >> r;
        a.add(i,r - l);
    }
    while(m--)
    {
        int sec;
        std::cin >> sec;
        if(sec == 1)
        {
            int x,y,k;
            std::cin >> x >> y >> k;
            a.add(x,y,k);
        }
        else
        {
            int it;
            std::cin >> it;
            std::cout << a.query(it) << '\n';
        }
    }


    return 0;
}