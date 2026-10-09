


#include<iostream>
#include<array>
#include<vector>
#include<bitset>


constexpr static int M_size{ 100000 + 2 };

struct disjoint_set
{
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

disjoint_set set;

std::vector<int> prime;
std::bitset<M_size> table;

void ola_sieve(int n)
{
    for(int i{ 2 }; i <= n;++i)
    {
        if(!table[i])
            prime.push_back(i);
        for(int j{}; i * prime[j] <= n;++j)
        {
            table.set(i * prime[j]);
            if(i % prime[j] == 0)
                break;
        }
    }
}


int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    int a,b,p;
    std::cin >> a >> b >> p;
    int it{};
    ola_sieve(b);
    while(prime[it] < p)
        ++it;
    for(; it != prime.size();++it)
    {
        for(int val = prime[it]; val + prime[it] <= b;val += prime[it])
        {
            if(val >= a)
                set.merge(val,val + prime[it]);
        }
    }
    size_t ans{};
    for(int i{ a }; i <= b;++i)
    {
        if(set.a[i] < 0)
            ++ans;
    }

    std::cout << ans;

    return 0;
}
