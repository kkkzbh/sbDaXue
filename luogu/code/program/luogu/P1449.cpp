


#include<iostream>
#include<stack>
#include<cctype>

using ll = long long;

int cau(ll x,ll y,int c)
{
    if(c == '+') return x + y;
    if(c == '-') return x - y;
    if(c == '/') return x / y;
    if(c == '*') return x * y;
    return 0;
}

inline int ctoi(int c){ return c - '0'; }

int main()
{
    std::stack<ll> stk;
    int c;
    ll val{};
    while((c = std::cin.get()) != '@')
    {
        if(c == '.') stk.push(val),val = 0;
        else if(isdigit(c))
        {
            val *= 10;
            val += ctoi(c);
        }
        else
        {
            ll x1 = stk.top();
            stk.pop();
            ll x2 = stk.top();
            stk.pop();
            stk.push(cau(x2,x1,c));
        }
    }
    std::cout << stk.top();

    return 0;
}