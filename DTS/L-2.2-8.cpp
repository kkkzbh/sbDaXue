

#if 1
#include<iostream>
#include<stack>

int isleft(char& c)
{
    if(c == '(') return 1;
    if(c == '[') return 2;
    if(c == '{') return 3;
    if(c == '*') return 4;
    return 0;
}

int isright(char& c)
{
    if(c == ')') return 1;
    if(c == ']') return 2;
    if(c == '}') return 3;
    if(c == '/') return 4;
    return 0;
}

int main()
{
    char c;
    std::stack<char> stk;
    bool flag = true;
    while(flag && std::cin.get(c))
    {
        if(c == '.' && (c = static_cast<char>(std::cin.get())) == '\n') break;
        if(c == '/')    //因为/* */的双字符性质 只得特判
        {
            while((c = static_cast<char>(std::cin.get())) == '/');
            if(c =='*') stk.push(c);
            continue;
        }
        if(c == '*')
        {
            while((c = static_cast<char>(std::cin.get())) == '*');
            if(isright(c))
            {
                if(stk.empty() || isleft(stk.top()) != isright(c)) flag = false;
                else stk.pop();
            }
            continue;
        }
        if(isleft(c))
        {
            stk.push(c);
        }
        else if(isright(c))
        {
            if(stk.empty() || isleft(stk.top()) != isright(c)) flag = false;
            else stk.pop();
        }
    }
    if(stk.empty() && flag) std::cout << "YES";
    else
    {
        std::cout << "NO\n";
        char tmp;
        if(!stk.empty())
        {
            if(flag) while(!stk.empty()) tmp = stk.top(),stk.pop();
            else tmp = stk.top();
            if (tmp != '*') std::cout << tmp << "-?";
            else std::cout << "/*-?";
#if 0
            if (isleft(tmp))
            {
                if (tmp != '*') std::cout << tmp << "-?";
                else std::cout << "/*-?";
            }
            else
            {
                if (tmp != '*') std::cout << "?-" << tmp;
                else std::cout << "?-*/";
            }
#endif
        }
        else
        {
            if(c != '/') std::cout << "?-" << c;
            else std::cout << "?-*/";
        }
    }

    return 0;
}

#endif


