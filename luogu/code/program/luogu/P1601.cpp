

#ifdef P1601

#include<iostream>
#include<string>

constexpr int size = 513;

char lv[size];
char rv[size];
int vc[size];
int ltop = 0;
int rtop = 0;

void swap(char& a,char& b)
{
    char tmp = a;
    a = b;
    b = tmp;
}

void reverse(int st,int end,char* arr)
{
    while(st < end)
    {
        swap(arr[st++],arr[end--]);
    }
}

int main()
{
    char v;
    std::string s;
    std::cin >> s;
    for(auto v : s)
    {
        lv[++ltop] = v - '0';
    }
    std::cin >> s;
    for(auto v : s)
    {
        rv[++rtop] = v - '0';
    }
    reverse(1,ltop,lv);
    reverse(1,rtop,rv);
    int max = ltop > rtop ? ltop : rtop;
    int fix = 0;
    int value = 0;
    for(int i = 1;i <= max + 1;++i)
    {
        value = lv[i] + rv[i];
        vc[i] = static_cast<char>((value+ fix) % 10);
        fix = (value + fix) / 10;
    }
    int i;
    for(i = max + 1;vc[i] == 0;--i);
    if(i >= 1)
        for(;i >= 1;--i) std::cout << vc[i];
    else
        std::cout << 0;
    return 0;
}

#endif
