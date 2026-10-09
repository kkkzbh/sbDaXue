

#ifdef P1603

#include<iostream>
#include<string>

int todig(const std::string& str)
{
    if(str == "zero") return 0;
    if(str == "one" || str == "a" || str == "another" || str == "first")
        return 1;
    if(str == "two" || str == "both" || str == "second") return 2;
    if(str == "three" || str == "third") return 3;
    if(str == "four") return 4;
    if(str == "five") return 5;
    if(str == "six") return 6;
    if(str == "seven") return 7;
    if(str == "eight") return 8;
    if(str == "nine") return 9;
    if(str == "ten") return 10;
    if(str == "eleven") return 11;
    if(str == "twelve") return 12;
    if(str == "thirteen") return 13;
    if(str == "fourteen") return 14;
    if(str == "fifteen") return 15;
    if(str == "sixteen") return 16;
    if(str == "seventeen") return 17;
    if(str == "eighteen") return 18;
    if(str == "nineteen") return 19;
    if(str == "twenty") return 20;
    return -1;
}

void insert_sort(int* a,const int* b)
{
    if(a == b) return;
    for(int* it = a + 1;it != b;++it)
    {
        int value = *it;
        int* i = it;
        for(;i != a && value < *(i-1);--i) *i = *(i-1);
        *i = value;
    }
}

int main()
{
    int v[10]{};
    int top = -1;
    std::string s;
    while(std::cin >> s && s[0] != '.')
    {
        int value = todig(s);
        if(value != -1)
        {
            v[++top] = (value * value) % 100;
        }
    }
    insert_sort(v,v + top + 1);
    int i = 0;
    while(i <= top && v[i] == 0) ++i;
    if(i <= top)
    {
        std::cout << v[i++];
        for (; i <= top; ++i)
        {
            if (v[i] < 10) std::cout << 0 << v[i];
            else std::cout << v[i];
        }
    }
    else std::cout << 0;

    return 0;
}

#ifdef ABANDON
#include<iostream>
#include<sstream>
#include<string>

constexpr int size = 50;
int v[size]{};
int top = -1;
std::string vstr;
std::string vs[size];
int vi = -1;

int todig(const std::string& str)
{
    if(str == "zero") return 0;
    if(str == "one" || str == "a" || str == "another" || str == "first")
        return 1;
    if(str == "two" || str == "both" || str == "second") return 2;
    if(str == "three" || str == "third") return 3;
    if(str == "four") return 4;
    if(str == "five") return 5;
    if(str == "six") return 6;
    if(str == "seven") return 7;
    if(str == "eight") return 8;
    if(str == "nine") return 9;
    if(str == "ten") return 10;
    if(str == "eleven") return 11;
    if(str == "twelve") return 12;
    if(str == "thirteen") return 13;
    if(str == "fourteen") return 14;
    if(str == "fifteen") return 15;
    if(str == "sixteen") return 16;
    if(str == "seventeen") return 17;
    if(str == "eighteen") return 18;
    if(str == "nineteen") return 19;
    if(str == "twenty") return 20;
    return -1;
}

void conversion(std::string& str)
{
    int value = todig(str);
    std::string tmp;
    std::ostringstream os;
    if(value != -1)
    {
        value = (value * value) % 100;
        ++top;
        v[++top] = value % 10;
        v[top - 1] = value / 10;
        os << value;
        tmp = os.str();
        os.str("");
        if(tmp.size() == 1) tmp = '0' + tmp;
        vstr += tmp;
        vs[++vi] = tmp;
    }
}

void insert_sort(int* a,int* b)
{
    for(int* it = a + 1;it != b;++it)
    {
        int value = *it;
        int* i = it;
        for(;i != a && value < *(i-1);--i) *i = *(i-1);
        *i = value;
    }
}

bool cmp(std::string s1,std::string s2)
{
    if(s1[0] != s2[0]) return s1[0] - s2[0];
    return s1[1] - s2[1];
}

int main()
{
    std::string s;
    while(std::cin >> s && s[0] != '.')
    {
        conversion(s);
    }
    for(auto it : v) std::cout << it;
    std::cout << '\n';
    insert_sort(v ,*(&v + 1));
    for(auto it : v)
    {
        if(it) std::cout << it;
    }

    return 0;
}
#endif

#endif
