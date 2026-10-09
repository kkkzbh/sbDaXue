

#ifdef P1308

#include<iostream>
#include<string>
#include<cctype>

void tol(std::string& str)
{
    for(auto &it : str)
    {
        it = tolower(it);
    }
}

int main()
{
    std::string c;
    std::string str;
    std::getline(std::cin,c);
    std::getline(std::cin,str);
    tol(c);
    tol(str);
    c = ' ' + c + ' ';
    str = ' ' + str + ' ';
    int count = 0;
    int pos = 0;
    int p = 0;
    if((pos = str.find(c)) == std::string::npos)
    {
        std::cout << -1;
    }
    else
    {
        ++count;
        p = pos;
        while((p = str.find(c,p + 1)) != std::string::npos)
        {
            ++count;
        }
        std::cout << count << ' ' << pos;
    }

    return 0;
}

#endif
