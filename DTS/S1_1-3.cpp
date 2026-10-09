

#ifdef S1_1_3

#include<iostream>
#include<string>
#include<stack>
#include<cctype>

constexpr int size = 20 + 10;

inline int conversion(char c)
{
    switch(c)
    {
        case '(' : return 1;
        case '+' :
        case '-' : return 2;
        case '*' :
        case '/' : return 3;
        default  : return -1;
    }
}

int main()
{
    std::string s;
    std::cin >> s;
    int num = 0;
    std::string ans;
    std::stack<char> stk;
    int isprint = 0;
    int flag = 0;
    char f = 0;
    for(char c : s)
    {
        if(isdigit(c) || c == '.' || (((flag == 1 || !isprint) && f != ')') && (c == '+' || c == '-')))
        {
            if(flag && isprint) ans += ' ';
            flag = 0;
            if(c != '+')  ans += c;
            isprint = 1;
        }
        else
        {
            flag = 1;
            f = c;
            if(c != ')' && c != '(')
            {
                while(!stk.empty() && conversion(stk.top()) >= conversion(c))
                {
                    if(isprint) ans += ' ';
                    ans += stk.top();
                    stk.pop();
                    isprint = 1;
                }
                stk.push(c);
            }
            else if(c == ')')
            {
                while(stk.top() != '(')
                {
                    if(isprint) ans += ' ';
                    ans += stk.top();
                    stk.pop();
                    isprint = 1;
                }
                stk.pop();
            }
            else stk.push(c);
        }
    }
    while(!stk.empty())
    {
        if(isprint)
            ans += ' ';
        ans += stk.top();
        stk.pop();
        isprint = 1;
    }
    for(auto it : ans)
    {
        std::cout << it;
    }

    return 0;
}

#endif