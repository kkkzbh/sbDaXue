

#include<iostream>
#include<bitset>

constexpr int M_size{ 1000 + 2 };

constexpr std::bitset<M_size> a_erlich_sieve(int left,int right)
{
    std::bitset<M_size> v(3);  //利用所有数都可质分解 利用质数筛除素数
    for(int i{ 2 },cei{ right / i }; i <= cei;++i)
    {
        if(!v[i])
            for(int k{ i * i }; k <= right;k += i)
                v.set(k);
    }
    return v;
}

int main()
{
	auto v = a_erlich_sieve(10,20);
		
	for(int i = 10; i <= 20;++i)
	{
		if(!v[i])
			std::cout << i << ' ';
	}
		
	return 0;
}
