

#include"header/print.h"
#include<array>

constexpr int M_size = { (1 << 8) + 5 };

std::array<std::array<char,M_size>,M_size> a;

auto M_FILL = []() -> auto
{
    for(auto&& i : a)
        i.fill(32);
    return 0;
}();

void print(int n)
{
    if(n == 1)
        a[1][1] = '*';
    else
    {
        print(n - 1);
        for(int i{ 1 }; i <= (1 << (n - 2));++i)
            for(int j{ (1 << (n - 2)) + 1 }; j <= (1 << (n - 1));++j)
                a[i][j] = a[i][j - (1 << (n - 2))];
        for(int i{ (1 << (n - 2)) + 1 }; i <= (1 << (n - 1));++i)
            for(int j{ 1 }; j <= (1 << (n - 2));++j)
                a[i][j] = a[i - (1 << (n - 2))][j];
    }
}

int n;
void print()
{
    for(int i{ 1 }; i <= (1 << (n - 1));++i)
    {
        for (int j{ 1 }; j <= (1 << (n - 1)); ++j)
            print("{}",a[i][j]);
        print('\n');
    }
}

int main()
{
    std::cin >> n;
    print(n);
    print();


    return 0;
}