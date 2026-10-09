

#include<iostream>
#include<array>
#include<tuple>
#include<format>

using size = std::size_t;

constexpr size M_size = 1000;

int main()
{
    std::array<std::tuple<int,int,int>,M_size> a{};
    std::array<int,M_size> num{};   //index 有 a[index]个
    std::array<int,M_size> cpot{};  //num前缀和 表起始位置
    a[0] = std::make_tuple(1,2,10);
    a[1] = std::make_tuple(1,5,12);
    a[2] = std::make_tuple(2,3,2);
    a[3] = std::make_tuple(2,4,2);
    a[4] = std::make_tuple(2,5,100);
    a[5] = std::make_tuple(3,2,1);
    std::cout << "i\t\tj\t\tval\n";
    for(int i = 0; i != 6;++i)
    {
        std::cout << std::format("{}\t\t{}\t\t{}\n",std::get<0>(a[i]),std::get<1>(a[i]),std::get<2>(a[i]));
    }

    for(int i = 0; i != 6;++i)
    {
        ++num[std::get<1>(a[i])];
    }

    cpot[0] = 0;
    for(int i = 1; i != 6;++i)
    {
        cpot[i] = cpot[i - 1] + num[i - 1];
    }

    //转置
    std::array<std::tuple<int,int,int>,M_size> b{};

    for(int i = 0; i != 6;++i)
    {
        std::get<0>(b[cpot[std::get<1>(a[i])]]) = std::get<1>(a[i]);
        std::get<1>(b[cpot[std::get<1>(a[i])]]) = std::get<0>(a[i]);
        std::get<2>(b[cpot[std::get<1>(a[i])]]) = std::get<2>(a[i]);
        ++cpot[std::get<1>(a[i])];
    }
    std::cout << "\ni\t\tj\t\tval  -->转置后\n";
    for(int i = 0; i != 6;++i)
    {
        std::cout << std::format("{}\t\t{}\t\t{}\n",std::get<0>(b[i]),std::get<1>(b[i]),std::get<2>(b[i]));
    }

    return 0;
}