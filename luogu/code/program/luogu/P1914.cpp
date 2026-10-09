

#ifdef P1914

#include<iostream>
#include<string>

int main()
{
    int n;
    std::string s;
    std::cin >> n >> s;

    for(auto& it : s)
    {
        int x = it + n;
        if(x > 'z') x -= 26;
        it = x;
    }
    std::cout << s;

    return 0;
}

#endif