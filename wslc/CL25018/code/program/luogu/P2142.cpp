

#ifdef P2142

#include<iostream>
#include<string>

constexpr int size = 10086 + 5;

int lv[size];
int rv[size];
int eq[size];
int sl,sr;

void make(const std::string& s,int arr[],int& top)
{
    top += s.size();
    int sz = top;
    for(auto it : s)
    {
        arr[sz--] = it - '0';
    }
}

bool cmp()  // 判断是不是负数
{
    if(sl != sr) return sl < sr;
    else
    {
        int top = 1;
        while(top <= sl && lv[top] == rv[top]) ++top;
        return top <= sl && lv[top] - rv[top] < 0;
    }
}

int sub()
{
    int islose = cmp();
    int max = sl > sr ? sl : sr;
    int* l = islose ? rv : lv;
    int* r = islose ? lv : rv;
    for(int i = 1;i <= max;++i)
    {
        eq[i] = l[i] - r[i];
        if(eq[i] < 0)
        {
            --l[i + 1];
            eq[i] += 10;
        }
    }
    return islose;
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
    int islose = sub();

    int max = sl > sr ? sl : sr;
    while(max > 1 && eq[max] == 0) --max;
    if(islose) std::cout << '-';
    for(;max > 0;--max) std::cout << eq[max];

    return 0;
}

#endif
