

#include<iostream>
#include<array>

template<typename Val>
struct Tarray
{
    using int64 = long long;
    constexpr static int M_size{ 500000 + 2 };

    std::array<Val,M_size> a{};
    int M_n;

    Tarray() = default;
    explicit Tarray(int sz) : M_n(sz){}
    void set(int sz)
    {
        M_n = sz;
    }

    void add(int i,Val val)
    {
        while(i <= M_n)
        {
            a[i] += val;
            i += i & -i;
        }
    }

    int64 query(int l,int r)
    {
        return query(r) - query(l - 1);
    }

private:

    int64 query(int i)
    {
        int64 ret{};
        while(i)
        {
            ret += a[i];
            i -= i & -i;
        }
        return ret;
    }

};

Tarray<int> a;

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int m;
    std::cin >> a.M_n >> m;
    for(int i{ 1 },val; i <= a.M_n; ++i)
    {
        std::cin >> val;
        a.add(i,val);
    }
    for(int i{ 1 },op,x,y; i <= m; ++i)
    {
        std::cin >> op >> x >> y;
        if(op == 1)
        {
            a.add(x,y);
        }
        else
        {
            std::cout << a.query(x,y) << '\n';
        }
    }


    return 0;
}