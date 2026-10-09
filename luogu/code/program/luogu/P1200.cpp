

#ifdef P1200

#include<iostream>
#include<string>

inline int ai(const std::string& str)
{
    int value = 1;
    for(auto it : str)
    {
        value *= (it - 'A' + 1);
    }
    return value;
}

int main()
{
    std::string s1;
    std::string s2;
    std::cin >> s1 >> s2;
    if(ai(s1) % 47 == ai(s2) % 47)
        std::cout << "GO";
    else
        std::cout << "STAY";

    return 0;
}

#endif
