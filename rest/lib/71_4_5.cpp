


#include<iostream>

constexpr int size = 1e4;

class table
{
    friend void reverse(int a,int b,int data[]);
private:
    int data[size]{};
    int top = 0;
public:
    table() : data{1,5,7,9,12,14,15,36,99},top(9){}
    void insert(int x);
    void print();
    void verse(int m,int);
    void verse(int m);
};

void table::insert(int x)
{
    if(top == size)
    {
        std::cerr << "The table is full!\n";
        return;
    }
    int it = 0;
    while(it != top && x > data[it]) ++it;
    for(int i = top; i != it;--i)
    {
        data[i] = data[i - 1];
    }
    data[it] = x;
    ++top;
}

void table::print()
{
    for(int i = 0; i != top;++i)
    {
        std::cout << data[i] << ' ';
    }
    std::cout << '\n';
}

void table::verse(int m,int)
{
    int n = top - m;
    if(m > n)
    {
        int* p = new int[n];
        for(int i = m;i != top;++i)
        {
            p[i - m] = data[i];
        }
        for(int i = m - 1; i != -1;--i)
        {
            data[i + n] = data[i];
        }
        for(int i = 0; i != n;++i)
        {
            data[i] = p[i];
        }
        delete[] p;
    }
    else
    {
        int*p = new int[m];
        for(int i = 0; i != m;++i)
        {
            p[i] = data[i];
        }
        for(int i = m; i != top;++i)
        {
            data[i - m] = data[i];
        }
        for(int i = n; i != top;++i)
        {
            data[i] = p[i - n];
        }
        delete[] p;
    }
}

template<typename T>
static void swap(T& a,T& b)
{
    T c = a;
    a = b;
    b = c;
}

void reverse(int a,int b,int data[])
{
    --b;
    while(a < b) swap(data[a++],data[b--]); 
}


void table::verse(int m)
{
    reverse(0,m,data);
    reverse(m,top,data);
    reverse(0,top,data);
}

int main()
{
    table a;
    a.print();
    a.verse(3);
    a.print();
    a.verse(5);
    a.print();

    return 0;
}