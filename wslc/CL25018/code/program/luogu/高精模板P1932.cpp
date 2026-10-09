

#ifdef P1932

#include<iostream>
#include<string>
#include<cstring>


constexpr long long size = 1e6 + 10;

int lv[size];
int rv[size];
int eq[size];
int sl,sr;
int lenr;

void make(const std::string& s,int arr[],int& top)
{
    top += s.size();
    int sz = top;
    for(auto it : s)
    {
        arr[sz--] = it - '0';
    }
}

void add()
{
    int max = (sl > sr ? sl : sr) + 1;
    for(int i = 1;i < max;++i)
    {
        eq[i] += lv[i] + rv[i];
        eq[i + 1] = eq[i] / 10;
        eq[i] %= 10;
    }
    while(max > 1 && eq[max] == 0) --max;
    for(;max >= 1;--max) std::cout << eq[max];
    std::cout << '\n';
}

bool islose()
{
    if(sl != sr) return sl < sr;
    else
    {
        int top = sl;
        while(top >= 1 && lv[top] == rv[top]) --top;
        return top >= 1 && lv[top] < rv[top];
    }
}

void sub()
{
    memset(eq,0,sizeof(eq));
    bool flag = islose();
    int* l = flag ? rv : lv;
    int* r = flag ? lv : rv;
    int max = sl > sr ? sl : sr;
    for(int i = 1;i <= max;++i)
    {
        eq[i] += l[i] - r[i];
        if(eq[i] < 0)
        {
            --eq[i+1];
            eq[i] += 10;
        }
    }
    if(flag) std::cout << '-';
    while(max > 1 && eq[max] == 0) --max;
    for(;max >= 1;--max) std::cout << eq[max];
    std::cout << '\n';
}

void mul()
{
    memset(eq,0,sizeof(eq));
    for(int i = 1;i <= sl;++i)
    {
        for(int j = 1;j <= sr;++j)
        {
            eq[i + j - 1] += lv[i] * rv[j];
            eq[i + j] += eq[i + j - 1] / 10;
            eq[i + j - 1] %= 10;
        }
    }
    int sz = sl + sr;
    while(sz > 1 && eq[sz] == 0) --sz;
    for(;sz >= 1;--sz) std::cout << eq[sz];
    std::cout << '\n';
}

template<class T>
void swap(T& a,T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

void shift_right(int n)
{
    if(n <= 0) return;
    for(int i = sr; i>= 1;--i)
    {
        swap(rv[i],rv[i + n]);
    }
    sr += n;
}

void shift_left()
{
    for(int i = sr - lenr;i <= sr;++i)
    {
        swap(rv[i],rv[i - 1]);
    }
    sr -= 1;
}

bool greater(const int* l,const int* r)
{
    int max = sl > sr ? sl : sr;
    for(; max > 0 && l[max] == r[max];--max);
    return l[max] >= r[max];
}

void sub(int* l,const int* r)
{
    int max = sl;
    for(int i = 1;i <= max;++i)
    {
        l[i] -= r[i];
        if(l[i] < 0)
        {
            --l[i + 1];
            l[i] += 10;
        }
    }
    while(sl > 1 && l[sl] == 0) --sl;
}

void div()
{
    memset(eq,0,sizeof(eq));
    int i = sl - sr;
    int pos = 0;
    if(i < 0)
    {
        std::cout << 0 << '\n';
        return;
    }
    shift_right(i);
    for(;i >= 0;--i)
    {
        int count = 0;
        while(greater(lv,rv))
        {
            sub(lv,rv);
            ++count;
        }
        eq[++pos] = count;
        shift_left();
    }
    while(i < pos && eq[i] == 0) ++i;
    for(;i<=pos;++i)
    {
        std::cout << eq[i];
    }
    std::cout << '\n';
}

void mod()
{
    for(int i = sl;i >= 1;--i)
        std::cout << lv[i];
    std::cout << '\n';
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::string s;
    std::cin >> s;
    make(s,lv,sl);
    std::cin >> s;
    make(s,rv,sr);
    add();
    sub();
    mul();

    lenr = sr;
    div();
    mod();

    return 0;
}

#endif
