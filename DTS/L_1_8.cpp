

#ifdef L_1_8

#include<iostream>
#include<algorithm>
constexpr int size = 2 * 100 + 10;

template<typename T>
void reverse(T* a,T* b)
{
    while(a < b)
    {
        std::swap(*a++,*b--);
    }
}

int main()
{
    int n,m;
    std::cin >> n >> m;
    int a[size];
    for(int i = 1; i <= n;++i)
    {
        std::cin >> a[i];
    }
    m %= n;
    reverse(a + 1,a + m);
    reverse(a + m + 1,a + n);
    reverse(a + 1,a + n);
    int flag = 1;
    for(int i = 1; i <=n ;++i)
    {
        if(flag) flag = 0;else std::cout << ' ';
        std::cout << a[i];
    }
    return 0;
}

#endif
