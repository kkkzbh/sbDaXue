
#include<iostream>

constexpr int size = 1e4;

class table
{
private:
    char data[size]{};
    int top = 0;
public:
    table() : data{'&','B','7','A','Z','3','P',']','#','D','C','9','2','7','!'},top(15){}
    void sort();
    void print();
};

template<typename T>
inline void swap(T* a,T* b)
{
    T c = *a;
    *a = *b;
    *b = c;
}

inline int isalpha(int c)
{
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

inline int isdigit(int c)
{
    return c >= '0' && c <= '9';
}

void table::sort()
{
    char* left = data - 1;
    char* right = data + top;
    while(left < right)
    {
        while(isalpha(*++left));
        while(!isalpha(*--right));
        if(left < right) swap(left,right);
    }
    right = data + top;
    while(left < right)
    {
        while(isdigit(*++left));
        while(!isdigit(*--right));
        if(left < right) swap(left,right);
    }
}

inline void table::print()
{
    for(int i = 1; i <= top;++i)
    {
        std::cout << data[i] << ' ';
    }
    std::cout << '\n';
}

int main()
{
    table a;
    a.print();
    a.sort();
    a.print();

    return 0;
}