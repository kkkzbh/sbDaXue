

#ifdef P5018

#include<iostream>
#include<string>

int main()
{
    std::string s;
    std::getline(std::cin,s);
    int count = 0;
    for(const auto& it : s)
    {
        if(it != ' ') ++count;
    }

    std::cout << count;

    return 0;
}

#endif
