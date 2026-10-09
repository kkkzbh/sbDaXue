


#include<iostream>
#include<array>

struct disjoint_set
{
    constexpr static int M_size{ 100000 + 2 };
    std::array<int,M_size> a;
    disjoint_set(){ a.fill(-1); }
    int find(int x) noexcept
    {
        if(a[x] > -1)
            return a[x] = find(a[x]);
        return x;
    }
    void merge(int x,int y) noexcept
    {
        int fx = find(x);
        int fy = find(y);
        if(fx != fy)
        {
            if(a[fx] < a[fy])
            {
                a[fy] += a[fx];
                a[fx] = fy;
            }
            else
            {
                a[fx] += a[fy];
                a[fy] = fx;
            }
        }
    }
    bool same(int x,int y)
    {
        return find(x) == find(y);
    }
};

constexpr int M_size{ 100000 + 2 };

constexpr bool is_prime(int x)
{
    if(x <= 1)
        return false;
    for(int i{ 2 }; i * i <= x;++i)
    {
        if(!(x % i))
            return false;
    }
    return true;
}

constexpr auto M_prime()
{
    std::array<int,M_size> a{};
    int top{};
    for(int i{ 2 }; i != M_size;++i)
    {
        if(is_prime(i))
            a[top++] = i;
    }
    return std::make_pair(a,top);
}

auto P_prime = M_prime();
auto& prime = P_prime.first;
auto& top = P_prime.second;
disjoint_set set;

int main()
{
    int a,b,p;
    std::cin >> a >> b >> p;    //求 最大公共质因数 a,b,px
    int t{};
    while(prime[t] < p && t != top) ++t;
    for(int i{ a }; i < b;++i)
    {
        for(int j{ i + 1 }; j <= b;++j)
        {
            for(int k{ t }; k != top; ++k)
            {
                if(!(i % prime[k] || j % prime[k]))
                {
                    set.merge(i,j);
                    break;
                }
            }
        }
    }
    size_t ans{};
    for(int i{ a },sz{ b }; i <= sz;++i)
    {
        if(set.a[i] < 0)
            ++ans;
    }
    std::cout << ans;

    return 0;
}