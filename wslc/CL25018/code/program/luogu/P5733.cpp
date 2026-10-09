


#ifdef P5733

#include<iostream>

constexpr int size = 100 + 10;
char str[size];

inline int islower(int c)
{
    return c >= 'a' && c <= 'z';
}

inline int toupper(int c)
{
    return c - 32;
}

int main()
{
    std::cin >> str;
    char* it = str;
    while(*it)
    {
        if(islower(*it))
        {
            *it = toupper(*it);
        }
        ++it;
    }
    std::cout << str;

    return 0;
}


#endif