

#include<iostream>
#include<vector>
#include<bitset>


constexpr int M_size{ 100000000 + 2 };

std::bitset<M_size> table;
std::vector<int> prime;


void ola_sieve(int n)
{
    for(int i{ 2 }; i <= n;++i)
    {
        if(!table[i])
        {
            prime.push_back(i);
        }
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
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int n,q;
    std::cin >> n >> q;
    ola_sieve(n);
    while(q--)
    {
        int k;
        std::cin >> k;
        std::cout << prime[k - 1] << '\n';
    }


    return 0;
}