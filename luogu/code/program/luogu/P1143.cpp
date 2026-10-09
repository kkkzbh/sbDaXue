


#include<iostream>
#include<stack>
#include<array>
#include<cctype>
#include<string>
#include<limits>

int hash(char c)
{
    if(isdigit(c))
        return c ^ 48;
    else
        return 9 + (c ^ 64);
}

char hash(int c)
{
    if(c < 10)
        return c ^ 48;
    else
        return (c - 9) ^ 64;
}

int main()
{
    int n;
    std::cin >> n;
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(),10);
    std::string s;
    //std::getline(std::cin,s);
    std::cin >> s;
    int val{};
    for(auto&& c : s)
    {
        val *= n;
        val += hash(c);
    }
    int m;
    std::cin >> m;
    std::stack<int> stk;
    while(val)
    {
        stk.push(val % m);
        val /= m;
    }
    while(!stk.empty())
    {
        std::cout << hash(stk.top());
        stk.pop();
    }


    return 0;
}