


#ifdef P1067

#include<iostream>

#include<array>

constexpr int size = 100 + 10;

struct v
{
    int index = 0;
    int power = 0;
    v() = default;
    v(int i,int p) : index(i), power(p){}
};

void print(const v& val)
{
    if(!val.index)
        return;
    if(val.power)
    {
        if(val.index < 0)
        {
            if(val.index == -1)
                std::cout << '-';
            else std::cout << val.index;
        }
        else if(val.index > 0)
        {
            if(val.index == 1)
                std::cout << '+';
            else std::cout << '+' << val.index;
        }
        if(val.power != 1)
            std::cout << "x^" << val.power;
        else std::cout << 'x';
    }
    else
    {
        if(val.index > 0)
            std::cout << '+' << val.index;
        else
            std::cout << val.index;
    }
}

int main()
{
    std::array<v,size> a{};
    int i = 1;
    int n;
    std::cin >> n;
    int value;
    while(n + 1)
    {
        std::cin >> value;
        a[i++] = v(value,n--);
    }
    if(a[1].power)
    {
        if(a[1].index < 0)
        {
            if(a[1].index == -1)
                std::cout << '-';
            else
                std::cout << a[1].index;
        }
        else if(a[1].index > 0)
        {
            if(a[1].index != 1)
                std::cout << a[1].index;
        }
        if(a[1].power != 1)
            std::cout << "x^" << a[1].power;
        else std::cout << 'x';
    }
    else
    {
        std::cout << a[1].index;
    }
    for(int x = 2; x < i;++x)
    {
        print(a[x]);
    }

    return 0;
}

#endif
