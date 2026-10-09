

#ifdef P1303

#include<iostream>
#include<string>

constexpr int size = 4060;
constexpr int sta = 9;
int a[size/2];
int sa = sta;
int b[size/2];
int sb = sta;
int c[size];
int sc = sta;

void make(const std::string& str,int arr[],int& top)
{
    top += str.size();
    int sz = top;
    for(auto it : str)
    {
        arr[sz--] = it - '0';
    }
}

void mul(int lv[],int& sl,int rv[],int& sr,int eq[])
{
    for(int i = sta + 1;i<=sl;++i)
    {
        for(int j = sta + 1;j<=sr;++j)
        {
            eq[i + j - 1] += lv[i] * rv[j];
            eq[i + j] += c[i + j - 1] / 10;
            eq[i + j - 1] %= 10;
        }
    }
}

void print(int eq[],int& sz)
{
    int s = sz;
    for(;s > 2 * sta + 1 && eq[s] == 0;--s);
    for(;s > 2 * sta;--s) std::cout << eq[s];
    std::cout << '\n';
}

int main()
{
    std::string s;
    std::cin >> s;
    make(s,a,sa);
    std::cin >> s;
    make(s,b,sb);
    mul(a,sa,b,sb,c);
    sc = sa + sb;
    print(c,sc);
    return 0;
}

#endif
