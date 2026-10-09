

#include<iostream>
#include<string>
#include<array>

constexpr int M_row{ 10 + 2 };
constexpr int M_cow{ 100 + 2 };

int n;
std::string str;
std::array<std::array<char,M_cow>,M_row> matrix;
int row,cow;

void set()
{
    for(auto&& i : matrix)
    {
        i.fill(32);
    }
}

auto M_set = []() -> auto
{
    set();
    return 0;
}();

void solve()
{
    size_t ir = 0;
    size_t ic = 0;
    for(size_t i{}; i != str.size();++i)
    {
        if(ic == n)
        {
            ic = 0;
            ++ir;
        }
        matrix[ir][ic++] = str[i];
    }
}

void print()
{
    for(int j{}; j != cow;++j)
    {
        for(int i{ row - 1 }; i >= 0;--i)
        {
            std::cout << matrix[i][j];
        }
        if(j != cow - 1)
            std::cout << '\n';
    }
}

int main()
{
    freopen("../in.in","r",stdin);
    freopen("../out.out","w",stdout);
    std::cin >> n;
    fgetc(stdin);
    std::getline(std::cin,str);
    cow = n;
    row = (str.size() - 1) / n + 1;
    solve();
    print();

    return 0;
}