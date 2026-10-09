

#include<iostream>
#include<stack>
#include<cctype>
#include<cmath>

int hash(int i)
{
    if(i < 10)
        return i ^ 48;
    return (i - 9) ^ 64;
}

struct Integer
{

    int val;
    Integer() = default;
    Integer(int i) : val(i){}
    operator int() const noexcept
    {
        return val;
    }

    Integer& operator/=(const Integer& a)
    {
        if(*this % a < 0)  //模出负数
            this->val += a.val;
        this->val /= a.val;
        return *this;
    }
};

Integer operator/(const Integer& a,const Integer& b)
{
    Integer c = a;
    return c /= b;
}
Integer operator%(const Integer& a,const Integer& b)
{
    int mod = a.val % b.val;
    if(mod < 0)
        mod += std::abs(b.val);
    return mod;
}
std::istream& operator>>(std::istream& is,Integer& a)
{
    is >> a.val;
    return is;
}


int main()
{
    int n;
    std::cin >> n;
    Integer val{ n };
    Integer r;
    std::cin >> r;
    std::stack<char> stk;
    while(val)
    {
        stk.push(hash(val % r));
        val /= r;
    }
    std::cout << n << '=';
    while(!stk.empty())
    {
        std::cout << stk.top();
        stk.pop();
    }
    std::cout << "(base" << r << ')';

    return 0;
}