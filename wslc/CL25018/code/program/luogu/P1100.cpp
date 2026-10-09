

#include<iostream>
#include<algorithm>

int main()
{
    int val;
    std::cin >> val;
#if 0
    std::swap(*reinterpret_cast<short*>(&val),
        *(reinterpret_cast<short*>(&val) + 1));
#endif

    val = (val >> 16) ^ (val << 16);


    std::cout << static_cast<unsigned>(val);
    return 0;
}