

#include<iostream>
#include<array>
#include<vector>

struct disjoint_set
{
    constexpr static int M_size{ 100000 + 2 };
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

constexpr bool is_prime(size_t p)
{
    if(p <= 1)
        return false;
    for(size_t i = 2; i * i <= p; ++i)
    {
        if(!(p % i))
            return false;
    }
    return true;
}

constexpr std::vector<int> linear_s(int left,int right)
{
    std::vector<int> v;
    for(int i{ left }; i <= right;++i)
    {
        if(is_prime(i))
            v.push_back(i);
    }
    return v;
}

disjoint_set set;

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    int a,b,p;
    std::cin >> a >> b >> p;
    const auto prime = linear_s(p,b);
    auto it = prime.begin();
    while(it != prime.end())
    {
        for(auto ad{ *it },val{ *it }; val + ad <= b; val += ad)
            if(val >= a)
                set.merge(val,val + ad);
        ++it;
    }
    int ans{};
    for(int i{ a }; i <= b;++i)
    {
        if(set.a[i] < 0)
            ++ans;
    }
    std::cout << ans;

    return 0;
}