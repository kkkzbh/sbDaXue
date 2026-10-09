

#ifdef P1042

#include<iostream>
#include<cmath>
#include<string>

void isWin(int& W,int& L)
{
    if(std::abs(W - L) >= 2)
    {
        std::cout << W << ':' << L << '\n';
        W = L = 0;
    }
}

int main()
{
    std::string s;
    int W = 0;
    int L = 0;
    char c;
    while((c = std::cin.get()) != 'E')
    {
        if(isalpha(c))
        {
            s += c;
        }
    }
    for(auto it : s)
    {
        if(it == 'W') ++W;
        else if(it == 'L') ++L;
        if(W >= 11 || L >= 11) isWin(W,L);
    }
    std::cout << W << ':' << L << "\n\n";
    W = L = 0;
    for(auto it : s)
    {
        if(it == 'W') ++W;
        else if(it == 'L') ++L;
        if(W >= 21 || L >= 21) isWin(W,L);
    }
    std::cout << W << ':' << L;

    return 0;
}

#endif
