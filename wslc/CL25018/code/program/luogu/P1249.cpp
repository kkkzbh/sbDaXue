

#ifdef P1249

#include<iostream>
#include<array>
constexpr int size = 150 + 10;
constexpr int sz = 10000;

void mul(std::array<int,sz>& a,int v,int& len)
{
    for(int i = 0; i < len;++i)
    {
        a[i] *= v;
    }
    for(int i = 0; i < len + 5;++i)
    {
        a[i + 1] += a[i] / 10;
        a[i] %= 10;
    }
    int i;
    for(i = len + 4;a[i] == 0;i--);
    len = i + 1;
}

int main()
{
    int n;
    std::cin >> n;
    std::array<int,size> a{};
    int top = -1;
    for(int i = 2; n >= i;i++)
    {
        n -= i;
        a[++top] = i;
    }
    int tmp = top;
    while(n--)
    {
        ++a[tmp--];
        if(tmp == -1) tmp = top;
    }
    for(int i = 0; i <= top;++i)
    {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';
    std::array<int,sz> value{};
    value[0] = 1;
    int len = 1;
    for(int i = 0; i <= top ; ++i)
    {
        mul(value,a[i],len);
    }
    for(int i = len - 1; i >= 0;--i)
    {
        std::cout << value[i];
    }

    return 0;
}

#endif
