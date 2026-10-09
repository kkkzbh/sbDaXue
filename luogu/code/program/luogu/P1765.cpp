

#ifdef P1765

#include<iostream>
#include<string>

int cnt(char c)
{
    if(c == 'a' || c == 'd' || c == 'g' || c == 'j' || c == 'm' || c == 'p' || c == 't' || c == 'w' || c == ' ')
        return 1;
    else if(c == 'b' || c == 'e' || c == 'h' || c == 'k' || c == 'n' || c == 'q' || c == 'u' || c == 'x')
        return 2;
    else if(c == 'c' || c == 'f' || c == 'i' || c == 'l' || c == 'o' || c == 'r' || c == 'v' || c == 'y')
        return 3;
    else if(c == 's' || c == 'z')
        return 4;
    return 0;
}

int main()
{
    std::string s;
    std::getline(std::cin,s);
    int count = 0;
    for(const auto &it : s)
    {
        count += cnt(it);
    }
    std::cout << count;

    return 0;
}

#endif
