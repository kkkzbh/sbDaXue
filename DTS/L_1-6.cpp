

#ifdef L_1_6

#include<iostream>
#include<array>

constexpr int size = 1e6 + 10;
std::array<int,size> a;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int K;
    std::cin >> K;
    int top = 1;
    int tmp = 0;
    while(std::cin >> tmp)
    {
        if(tmp < 0) break;
        a[top++] = tmp;
    }
    if(top - K <= 0) std::cout << "NULL";
    else std::cout << a[top - K];

    return 0;
}

#endif